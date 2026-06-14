
#include "png.hpp"
#include "../../display.hpp"

#ifdef IMAGE_SUPPORT_PNG

#if defined(__linux__) && !defined(memcpy_P)
#define memcpy_P memcpy
#endif

#include <PNGdec.h>

namespace ui {

PNG pngData;
shader_t pngShader;
Size pngSize;
Coords pngCoords;
time_t pngTime = 0;
size_t pngIndex = 0;
uint8_t pngTransparencyThreshold;

int pngRender(PNGDRAW *pDraw) {
	if (pDraw->y == 0) {
		pngIndex = 0;
	}

	int y = pngIndex / pngSize.x;
	int real_y = y + pngCoords.y;

	color_t pixels[pDraw->iWidth];
	uint8_t mask[pDraw->iWidth];

	pngData.getLineAsRGB565(pDraw, pixels, PNG_RGB565_LITTLE_ENDIAN, -1);
	pngData.getAlphaMask(pDraw, mask, pngTransparencyThreshold);

	for (int x = 0; x < pDraw->iWidth; x++) {
		// Don't render any transparent pixels.
		if (!(mask[x / 8] >> (7 - x % 8) & 1)) {
			continue;
		}

		int real_x = pngCoords.x + x;

		color_t pixel = pixels[x];
		if (pngShader) {
			pixel = pngShader(pixel, {x, y}, pngSize, pngTime);
		}

		drawPixel(real_x, real_y, pixel);
	}
	pngIndex += pDraw->iWidth;

	return 1;
}

void Png::renderAt(const Coords &coords, const shader_t &shader) const {
	pngTransparencyThreshold = transparencyThreshold;
	pngShader = shader;
	pngCoords = coords;
	pngSize = getSize();
	pngTime = millis();

	pngData.openRAM(bytes, length, pngRender);
	if (!pngData.isInterlaced()) {
		pngData.decode(nullptr, PNG_FAST_PALETTE);
	}
	pngData.close();
}

Size Png::getSize() const {
	size_t width = getInt(16, 4);
	size_t height = getInt(20, 4);

	return {width, height};
}

bool Png::isInterlaced() const {
	pngData.openRAM(bytes, length, pngRender);
	const bool val = pngData.isInterlaced();
	pngData.close();
	return value;
}

} // namespace ui

#else
#warning PNG rendering support is disabled.
#endif
