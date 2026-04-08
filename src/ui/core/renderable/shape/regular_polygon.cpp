#include "regular_polygon.hpp"
#include <cmath>

#define PI 3.141592653589

namespace ui {

RegularPolygon::RegularPolygon(color_t color, int pointCount, coord_t radius, bool fill, float angle) : Polygon(color, fill) {
	if (pointCount < 2) {
		return;
	}

	points.reserve(pointCount);
	for (int i = 0; i < pointCount; i++) {
		// Orient points so that a flat side is always downwards.
		float index = 2 * PI * i / pointCount + angle - PI / pointCount;
		coord_t x = std::sin(index) * radius;
		coord_t y = std::cos(index) * radius;

		points.push_back({x, y});
	}
}

} // namespace ui
