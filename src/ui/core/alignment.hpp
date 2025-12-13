/// @file alignment.hpp
#pragma once

#include <cinttypes>

namespace ui {

/**
 * @brief The various ways a child widget can be aligned in its parent.
 */
enum align_t {
	ALIGN_CENTER,
	ALIGN_LEFT = 1,
	ALIGN_RIGHT = 2,
	ALIGN_TOP = 1,
	ALIGN_BOTTOM = 2,
};

/**
 * @brief A struct that holds a widget's vertical and horizontal alignment.
 */
struct Alignment {
	/// @brief The horizontal alignment of the widget.
	align_t h;
	/// @brief The vertical alignment of the widget.
	align_t v;
};

} // namespace ui
