/// @file regular_polygon.hpp
#pragma once

#include "polygon.hpp"

namespace ui {

/**
 * @brief A polygon specialization for regular, convex polygons.
 */
struct RegularPolygon : public Polygon {
	/**
	 * @brief Construct the polygon.
	 * @param color The color of the polygon.
	 * @param points The number of points in the polygon.
	 * @param radius The distance each point is from the center.
	 * @param fill Whether to fill the polygon or just draw an outline.
	 * @param angle The initial rotation of the polygon.
	 */
	RegularPolygon(color_t color, int points, coord_t radius, bool fill = false, float angle = 0);
};

} // namespace ui
