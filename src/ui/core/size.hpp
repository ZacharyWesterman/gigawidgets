/// @file size.hpp
#pragma once

#include <cinttypes>

namespace ui {

/**
 * @typedef uisize_t
 * @brief A non-negative size for UI widgets.
 */
typedef uint16_t uisize_t;

/**
 * @brief A struct that holds the number of pixels that a widget would take up on the screen.
 */
struct Size {
	/// @brief The width of the widget.
	uisize_t x;
	/// @brief The height of the widget.
	uisize_t y;
};

} // namespace ui
