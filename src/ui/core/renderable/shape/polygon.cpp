#include "polygon.hpp"
#include "../../display.hpp"

namespace ui {

Polygon::Polygon(color_t color, const std::initializer_list<Coords> &&points) : color(color), points(points) {}

Polygon::Polygon(color_t color) : color(color) {}

void Polygon::renderAt(const Coords &coords, const shader_t &shader) const {
	if (points.size() < 2) {
		return;
	}

	Bounds bounds = getBounds();
	Size size = {bounds.max.x - bounds.min.x, bounds.max.y - bounds.min.y};
	time_t now = millis();

	for (size_t i = 0; i < points.size(); i++) {
		const size_t prev = (i ? i : points.size()) - 1;
		const size_t next = i;

		const Coords from{
			coords.x + points[prev].x - bounds.min.x,
			coords.y + points[prev].y - bounds.min.y,
		};
		const Coords to{
			coords.x + points[next].x - bounds.min.x,
			coords.y + points[next].y - bounds.min.y,
		};

		// Bit of a hack for performance:
		// polygons don't run shaders on a per-pixel basis;
		// instead they're run per-line.
		// This is fine for shaders like negative, grayscale, etc.
		color_t pixelColor = shader ? shader(color, {from.x, from.y}, size, now) : color;
		drawLine(from.x, from.y, to.x, to.y, pixelColor);
	}
}

Size Polygon::getSize() const {
	Bounds bounds = getBounds();

	return {bounds.max.x - bounds.min.x, bounds.max.y - bounds.min.y};
}

Bounds Polygon::getBounds() const {
	coord_t min_x = 0;
	coord_t min_y = 0;
	coord_t max_x = 0;
	coord_t max_y = 0;

	for (size_t i = 0; i < points.size(); i++) {
		const coord_t x = points[i].x;
		const coord_t y = points[i].y;

		if (x < min_x) {
			min_x = x;
		} else if (x > max_x) {
			max_x = x;
		}

		if (y < min_y) {
			min_y = y;
		} else if (y > max_y) {
			max_y = y;
		}
	}

	return {
		{min_x, min_y},
		{max_x, max_y},
	};
}

} // namespace ui
