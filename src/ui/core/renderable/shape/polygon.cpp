#include "polygon.hpp"
#include "../../display.hpp"

namespace ui {

Polygon::Polygon(color_t color, const std::initializer_list<Coords> &&points, bool fill) : fill(fill), color(color), points(points) {}

Polygon::Polygon(color_t color, bool fill) : fill(fill), color(color) {}

void Polygon::renderAt(const Coords &coords, const shader_t &shader) const {
	if (points.size() < 2) {
		return;
	}

	Bounds bounds = getBounds();
	Size size = {bounds.max.x - bounds.min.x, bounds.max.y - bounds.min.y};
	time_t now = millis();

	// Non-filled polygons are simpler.
	if (!fill) {
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
		return;
	}

	// Filled polygons are more complex

	coord_t intersect[points.size() / 2];
	uint8_t intersect_ct = 0;

	for (coord_t y = bounds.min.y; y <= bounds.max.y; y++) {
		// Find all intersections, sorted in order of X coord.
		intersect_ct = 0;
		for (size_t i = 0; i < points.size(); i++) {
			size_t prev = (i ? i : points.size()) - 1;
			size_t next = i;

			if (points[prev].y > points[next].y) {
				auto temp = prev;
				prev = next;
				next = temp;
			}

			const coord_t y0 = points[prev].y;
			const coord_t y1 = points[next].y;
			const coord_t x0 = points[prev].x;
			const coord_t x1 = points[next].x;

			if (points[prev].y > y || points[next].y < y) {
				// Doesn't intersect, skip.
				continue;
			}

			// Get the intersection X coord.

			const auto slope = (y1 - y0) / (float)(x1 - x0);

			// Make sure to handle slope zero

			const auto offset = y0 - slope * x0;
			coord_t x = (y - offset) / slope;

			// Insert intersection point in sorted order.
			bool duplicate = false;
			for (size_t n = 0; n < intersect_ct; n++) {
				const coord_t pt = intersect[n];
				// Within 1 pixel is a redundant intersection. Skip those.
				if (pt == x || pt + 1 == x || pt - 1 == x) {
					duplicate = true;
					break;
				}

				if (pt < x) {
					continue;
				}

				intersect[n] = x;
				x = pt;
			}

			if (duplicate) {
				continue;
			}

			intersect[intersect_ct++] = x;
		}

		// Draw lines in pairs of intersections.
		for (size_t i = 1; i < intersect_ct; i += 2) {
			const Coords from{
				coords.x + intersect[i - 1] - bounds.min.x,
				coords.y + y - bounds.min.y,
			};
			const Coords to{
				coords.x + intersect[i] - bounds.min.x,
				coords.y + y - bounds.min.y,
			};

			// Bit of a hack for performance:
			// polygons don't run shaders on a per-pixel basis;
			// instead they're run per-line.
			// This is fine for shaders like negative, grayscale, etc.
			color_t pixelColor = shader ? shader(color, {from.x, from.y}, size, now) : color;
			drawLine(from.x, from.y, to.x, to.y, pixelColor);
		}

		if (intersect_ct % 2) {
			for (size_t i = 0; i < intersect_ct; i++) {
				Serial.print(intersect[i]);
				Serial.print(" ");
			}
			Serial.println("");
		}
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
