#include "bitmap.hpp"
#include "../display.hpp"

namespace ui {

Size Bitmap::getSize() const {
	return size;
}

Bitmap::Bitmap(const Size &size, color_t *const data) : data(data) {
	this->size = size;
}

void Bitmap::renderAt(const Coords &coords, const shader_t &shader) const {
	time_t now = millis();

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

} // namespace ui
