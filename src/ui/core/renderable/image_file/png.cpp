
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

int pngRender(PNGDRAW *pDraw) {
	int y = pDraw->y;
	int real_y = pDraw->y + pngCoords.y;

	color_t pixels[pDraw->iWidth];
	pngData.getLineAsRGB565(pDraw, pixels, 0, -1);

	for (int x = 0; x < pDraw->iWidth; x++) {
		int real_x = pngCoords.x + x;

		color_t pixel = pixels[x];
		if (pngShader) {
			pixel = pngShader(pixel, {x, y}, pngSize, pngTime);
		}

		drawPixel(real_x, real_y, pixel);
	}

	return 1;
}

void Png::renderAt(const Coords &coords, const shader_t &shader) const {
	pngShader = shader;
	pngCoords = coords;
	pngSize = getSize();
	pngTime = millis();

	pngData.openRAM(bytes, length, pngRender);
	pngData.decode(nullptr, 0);
	pngData.close();
}

Size Png::getSize() const {
	return {0, 0}; // TODO: get image dimensions!
}

size_t Png::afterMarker(uint8_t marker, size_t startIndex) const {
	for (size_t i = startIndex + 1; i < length; i++) {
		if (bytes[i - 1] == 0xff && bytes[i] == marker) {
			return i + 1;
		}
	}

	return 0;
}

} // namespace ui

#else
#warning PNGdec library is not installed, so PNG rendering support is disabled.
#endif
