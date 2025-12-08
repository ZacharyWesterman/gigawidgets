#include "bounds.hpp"

namespace ui {

bool Bounds::contains(const Coords &point) {
	return point.x >= min.x && point.y >= min.y && point.x <= max.x && point.y <= max.y;
}

} // namespace ui
