#include "circle.hpp"
#include "../../display.hpp"

namespace ui {

Circle::Circle(color_t color, radius_t radius, bool fill) : color(color), radius(radius), fill(fill) {}

void Circle::renderAt(const Coords &coords, const shader_t &shader) const {
	drawCircle(coords.x + radius, coords.y + radius, radius, color, fill);
}

Size Circle::getSize() const {
	return {radius * 2, radius * 2};
}

} // namespace ui
