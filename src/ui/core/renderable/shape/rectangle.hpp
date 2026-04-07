/// @file rectangle.hpp
#pragma once

#include "polygon.hpp"

namespace ui {

/**
 * @brief A polygon specialization for rectangles.
 */
struct Rectangle : public Polygon {
	/**
	 * @brief Construct a rectangle from a color and size.
	 * @param color The color of the rectangle.
	 * @param size The size of the rectangle.
	 */
	Rectangle(color_t color, const Coords &size);
};

} // namespace ui
