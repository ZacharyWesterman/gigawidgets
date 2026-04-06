/// @file symmetric_polygon.hpp
#pragma once

#include "polygon.hpp"

namespace ui {

struct SymmetricPolygon : public Polygon {
	SymmetricPolygon(color_t color, int points, coord_t radius, float angle = 0);
};

} // namespace ui
