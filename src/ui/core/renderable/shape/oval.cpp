#include "oval.hpp"

namespace ui {

Oval::Oval(color_t color, radius_t radius1, radius_t radius2, float angle, bool fill) : fill(fill), color(color), radius1(radius1), radius2(radius2), angle(angle) {}

void Oval::renderAt(const Coords &coords, const shader_t &shader) const {}

Size Oval::getSize() const {
	const radius_t size = (radius1 > radius2 ? radius1 : radius2) * 2;
	return {size, size};
}

} // namespace ui
