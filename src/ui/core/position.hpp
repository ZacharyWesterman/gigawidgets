/// @file position.hpp
#pragma once

#include <cinttypes>

namespace ui {

/**
 * @brief A struct that holds the normalized position of a widget.
 *
 * Instead of a number of pixels, the value of each element is
 * expected to range from 0 to 1 inclusive, indicating far left
 * and far right on the parent widget, respectively.
 */
struct Position {
	/// @brief The normalized horizontal position.
	float x;
	/// @brief The normalized vertical position.
	float y;
};

} // namespace ui
