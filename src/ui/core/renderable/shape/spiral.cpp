#include "spiral.hpp"
#include "../../display.hpp"

#include <cmath>

namespace ui {

Spiral::Spiral(color_t color, float scale, coord_t innerRadius, float angleTotal, float angleStep) : color(color), scale(scale), innerRadius(innerRadius), angleTotal(angleTotal), angleStep(angleStep) {
	// Spirals are a bit complicated, so calculate the size on creation.

	float min = 0.f;
	float max = 0.f;

	for (float theta = angleStep; theta <= angleTotal; theta += angleStep) {
		float radius = innerRadius + scale * theta;

		float x = radius * std::cos(theta);
		float y = radius * std::sin(theta);

		if (x < min) {
			min = x;
		}
		if (x > max) {
			max = x;
		}
		if (y < min) {
			min = y;
		}
		if (y > max) {
			max = y;
		}
	}

	size = {
		max - min,
		max - min,
	};
}

void Spiral::renderAt(const Coords &coords, const shader_t &shader) const {
	const coord_t x_offset = size.x / 2 + coords.x;
	const coord_t y_offset = size.y / 2 + coords.y;

	coord_t prev_x = x_offset + innerRadius * std::cos(0);
	coord_t prev_y = y_offset + innerRadius * std::sin(0);

	for (float theta = angleStep; theta <= angleTotal; theta += angleStep) {
		float radius = innerRadius + scale * theta;

		coord_t x = x_offset + radius * std::cos(theta);
		coord_t y = y_offset + radius * std::sin(theta);

		drawLine(prev_x, prev_y, x, y, color);

		prev_x = x;
		prev_y = y;
	}
}

Size Spiral::getSize() const {
	return size;
}

} // namespace ui
