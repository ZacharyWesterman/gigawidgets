#include "ellipse.hpp"
#include "../../display.hpp"

namespace ui {

Ellipse::Ellipse(color_t color, radius_t radius1, radius_t radius2, bool fill) : fill(fill), color(color), radius1(radius1), radius2(radius2) {}

void Ellipse::renderAt(const Coords &coords, const shader_t &shader) const {
	color_t shapeColor = color;
	if (shader) {
		shapeColor = shader(shapeColor, coords, getSize(), millis());
	}

	drawEllipse(coords.x + radius1, coords.y + radius2, radius1, radius2, shapeColor, fill);
}

Size Ellipse::getSize() const {
	return {radius1 * 2, radius2 * 2};
}

} // namespace ui
