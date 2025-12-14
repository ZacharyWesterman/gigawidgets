#include "transparency_map.hpp"
#include "../display.hpp"

namespace ui {

TransparencyMap::TransparencyMap(const Size &size, color_t color, uint8_t *const mask) : size(size), color(color), mask(mask) {}

Size TransparencyMap::getSize() const {
	return size;
}

void TransparencyMap::renderAt(const Coords &coords, const shader_t &shader) const {
	time_t now = millis();

	color_t bw = (size.x + 7) / 8; // Bitmask scanline pad = whole byte
	uint8_t b = 0;
	for (coord_t y = 0; y < size.y; y++) {
		for (coord_t x = 0; x < size.x; x++) {
			if (x & 7) {
				b <<= 1;
			} else {
				b = mask[y * bw + x / 8];
			}
			if (b & 0x80) {
				color_t pixel = color;
				if (shader) {
					pixel = shader(pixel, {x, y}, size, now);
				}
				drawPixel(coords.x + x, coords.y + y, pixel);
			}
		}
	}
	endWrite();
}

} // namespace ui
