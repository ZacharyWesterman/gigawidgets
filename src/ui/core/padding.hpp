/// @file padding.hpp
#pragma once

#include <cinttypes>

#include "size.hpp"

namespace ui {

/**
 * @brief A struct that holds the padding that a parent widget may impose on a child widget.
 */
struct Padding {
	/// @brief The left padding.
	uisize_t left;
	/// @brief The top padding.
	uisize_t top;
	/// @brief The right padding.
	uisize_t right;
	/// @brief The bottom padding.
	uisize_t bottom;

	/**
	 * @brief Construct the padding with all sides equal.
	 * @param size The number of pixels to pad on the left, top, right and bottom.
	 */
	Padding(uisize_t size);

	/**
	 * @brief Construct the padding with parallel sides equal.
	 * @param left_right The number of pixels to pad on the left and right.
	 * @param top_bottom The number of pixels to pad on the top and bottom.
	 */
	Padding(uisize_t left_right, uisize_t top_bottom);

	/**
	 * @brief Construct the padding with all sides specified individually.
	 * @param left The number of pixels to pad on the left.
	 * @param top The number of pixels to pad on the top.
	 * @param right The number of pixels to pad on the right.
	 * @param bottom The number of pixels to pad on the bottom.
	 */
	Padding(uisize_t left, uisize_t top, uisize_t right, uisize_t bottom);
};

} // namespace ui
