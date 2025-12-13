/// @file bounds.hpp
#pragma once

#include "coords.hpp"

namespace ui {

/**
 * @brief A struct that holds the pixel space that a widget would take up on the screen.
 */
struct Bounds {
	/// @brief The starting point of the bounds.
	Coords min;
	/// @brief The ending point of the bounds.
	Coords max;

	/**
	 * @brief Check if a point is contained within the current bounds.
	 * @param point The point to check.
	 * @return True if the point is within the bounds or on the edge, false if outside the bounds.
	 */
	bool contains(const Coords &point);
};

} // namespace ui
