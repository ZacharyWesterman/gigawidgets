/// @file rectangle.hpp
#pragma once

#include "polygon.hpp"

namespace ui {

struct Rectangle : public Polygon {

	Rectangle(color_t color, const Coords &size);
};

} // namespace ui
