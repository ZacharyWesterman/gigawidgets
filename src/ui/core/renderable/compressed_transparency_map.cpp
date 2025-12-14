#include "compressed_transparency_map.hpp"
#include "../display.hpp"

namespace ui {

void CompressedTransparencyMap::renderAt(const Coords &coords, const shader_t &shader) const {
	time_t now = millis();
	endWrite();

	uint16_t i = 0;
	uint8_t count = mask[0];
	uint8_t byte = mask[1];
	for (coord_t y = 0; y < size.y; y++) {
		for (coord_t x = 0; x < size.x; x++) {
			if (x & 7) {
				byte <<= 1;
			} else {
				if (count == 0) {
					i += 2;
					count = mask[i];
				}
				byte = mask[i + 1];
				count--;
			}

			if (byte & 0x80) {
				color_t pixel = color;
				if (shader) {
					pixel = shader(pixel, {x, y}, size, now);
				}
				drawPixel(coords.x + x, coords.y + y, pixel);
			}
		}

		if (size.x & 7) {
			if (count == 0) {
				i += 2;
				count = mask[i];
			}
			byte = mask[i + 1];
			count--;
		}
	}
	endWrite();
}

} // namespace ui
