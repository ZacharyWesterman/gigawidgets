/// @file coords.hpp
#pragma once

#include <cinttypes>

namespace ui {

/**
 * @typedef coord_t
 * @brief A pixel coordinate on the screen. This can be negative or otherwise off-screen.
 */
typedef int16_t coord_t;

/**
 * @brief A struct for storing the pixel coordinates of various UI elements.
 */
struct Coords {
	/// @brief The horizontal coordinate.
	coord_t x;
	/// @brief The vertical coordinate.
	coord_t y;
};

} // namespace ui
