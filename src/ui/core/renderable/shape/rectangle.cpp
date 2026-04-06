#include "rectangle.hpp"

namespace ui {

Rectangle::Rectangle(color_t color, const Coords &size) : Polygon(color, {{0, 0}, {0, size.y}, {size.x, size.y}, {size.x, 0}}) {}

} // namespace ui
