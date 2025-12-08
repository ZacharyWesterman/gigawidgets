#include "bitmap.hpp"
#include "color.hpp"
#include "display.hpp"

namespace ui {

Size Bitmap::getSize() const {
	return size;
}

Bitmap::Bitmap(const Size &size, color_t *const data) : data(data) {
	this->size = size;
}

void Bitmap::renderAt(const Coords &coords, const shader_t &shader) const {
	time_t now = millis();

	startWrite();
	for (coord_t y = 0; y < size.y; y++) {
		for (coord_t x = 0; x < size.x; x++) {
			color_t pixel = data[y * size.x + x];
			if (shader) {
				pixel = shader(pixel, {x, y}, size, now);
			}
			drawPixel(coords.x + x, coords.y + y, pixel);
		}
	}
	endWrite();
}

color_t Bitmap::averageColor() const {
	uint32_t sum = 0;
	uint32_t count = size.x * size.y;
	for (uint32_t i = 0; i < count; i++) {
		sum += data[i];
	}
	return sum / count;
}

TransparentBitmap::TransparentBitmap(const Size &size, color_t *const data, uint8_t *const mask) : Bitmap(size, data), mask(mask) {}

void TransparentBitmap::renderAt(const Coords &coords, const shader_t &shader) const {
	time_t now = millis();

	color_t bw = (size.x + 7) / 8; // Bitmask scanline pad = whole byte
	uint8_t b = 0;
	startWrite();
	for (coord_t y = 0; y < size.y; y++) {
		for (coord_t x = 0; x < size.x; x++) {
			if (x & 7) {
				b <<= 1;
			} else {
				b = mask[y * bw + x / 8];
			}
			if (b & 0x80) {
				color_t pixel = data[y * size.x + x];
				if (shader) {
					pixel = shader(pixel, {x, y}, size, now);
				}
				drawPixel(coords.x + x, coords.y + y, pixel);
			}
		}
	}
	endWrite();
}

color_t TransparentBitmap::averageColor() const {
	color_t bw = (size.x + 7) / 8; // Bitmask scanline pad = whole byte
	uint8_t b = 0;

	uint32_t sum = 0;
	uint32_t count = 0;

	for (coord_t y = 0; y < size.y; y++) {
		for (coord_t x = 0; x < size.x; x++) {
			// Only sum up non-transparent pixels
			if (x & 7) {
				b <<= 1;
			} else {
				b = mask[y * bw + x / 8];
			}
			if (b & 0x80) {
				count++;
				sum += data[y * size.x + x];
			}
		}
	}
	return sum / count;
}

} // namespace ui
