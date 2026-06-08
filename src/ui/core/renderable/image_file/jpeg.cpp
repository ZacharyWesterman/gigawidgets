
#include "jpeg.hpp"
#include "../../display.hpp"

#ifdef IMAGE_SUPPORT_JPEG

#ifdef __linux__
#define memcpy_P memcpy
#endif

#include <Arduino.h>
#include <JPEGDEC.h>

namespace ui {

JPEGDEC jpegData;
shader_t jpegShader;
Size jpegSize;
Coords jpegCoords;
time_t jpegTime = 0;

int jpegRender(JPEGDRAW *pDraw) {
	for (int y = 0; y < pDraw->iHeight; y++) {
		int real_y = pDraw->y + y;

		for (int x = 0; x < pDraw->iWidth; x++) {
			int real_x = pDraw->x + x;

			if (real_x - jpegCoords.x >= jpegSize.x) {
				break;
			}

			color_t pixel = pDraw->pPixels[y * pDraw->iWidth + x];
			if (jpegShader) {
				pixel = jpegShader(pixel, {real_x, real_y}, jpegSize, jpegTime);
			}

			drawPixel(real_x, real_y, pixel);
		}
	}

	return 1;
}

void Jpeg::renderAt(const Coords &coords, const shader_t &shader) const {
	jpegShader = shader;
	jpegCoords = coords;
	jpegSize = getSize();
	jpegTime = millis();

	jpegData.openRAM(bytes, length, jpegRender);
	jpegData.decode(coords.x, coords.y, 0);
	jpegData.close();
}

Size Jpeg::getSize() const {
	const auto startOfFrame = afterMarker(0xc0);

	if (!startOfFrame) {
		// Error in the data, no "Baseline DCT" start of frame.
		return {0, 0};
	}

	// Assuming SOF0. more support to come in future.
	// const auto headerLength = getInt(startOfFrame, 2);
	// const auto precision = getInt(startOfFrame + 2, 1);
	const auto cols = getInt(startOfFrame + 3, 2);
	const auto rows = getInt(startOfFrame + 5, 2);
	// const auto imageComponents = getInt(startOfFrame + 7, 1);

	return {rows, cols};
}

size_t Jpeg::afterMarker(uint8_t marker, size_t startIndex) const {
	for (size_t i = startIndex + 1; i < length; i++) {
		if (bytes[i - 1] == 0xff && bytes[i] == marker) {
			return i + 1;
		}
	}

	return 0;
}

} // namespace ui

#else
#warning JPEGDEC library is not installed, so JPEG support is disabled.
#endif
