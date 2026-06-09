#include "bmp.hpp"
#include "../../color.hpp"
#include "../../display.hpp"
#include <Arduino.h>

#ifdef IMAGE_SUPPORT_BMP

namespace ui {

void Bmp::renderAt(const Coords &coords, const shader_t &shader) const {
	const auto size = getSize();
	const time_t now = millis();

	const size_t bitsPerPixel = getIntLE(28, 2);

	const size_t offset = getIntLE(14, 4) + 14;
	const size_t rowSize = ((bitsPerPixel * size.x + 31) / 32) * 4;
	const size_t pixelSize = bitsPerPixel / 8;

	for (size_t y = 0; y < size.y; y++) {
		for (size_t x = 0; x < size.x; x++) {
			size_t pixelIndex = y * rowSize + x * pixelSize + offset;

			auto b = bytes[pixelIndex + 0];
			auto g = bytes[pixelIndex + 1];
			auto r = bytes[pixelIndex + 2];

			auto pixel = rgb(r, g, b);

			if (shader) {
				pixel = shader(pixel, {x, y}, size, now);
			}

			drawPixel(x + coords.x, size.y + coords.y - y, pixel);
		}
	}
}

Size Bmp::getSize() const {
	size_t width = getIntLE(18, 4);
	size_t height = getIntLE(22, 4);

	return {width, height};
}

} // namespace ui

#else
#warning BMP rendering support is disabled.
#endif
