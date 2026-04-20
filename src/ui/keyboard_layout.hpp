/// @file keyboard_layout.hpp
#pragma once

namespace ui {
namespace layout {

/**
 * A generic interface for keyboard layouts.
 */
struct KeyboardLayout {
	/**
	 * @brief Get the first keyboard row.
	 * @param upper Whether to return shift/uppercase keys.
	 * @param alt Whether to return alt keys.
	 * @return A list of characters to display as keyboard buttons.
	 */
	virtual const char *row1(bool upper, bool alt) const = 0;

	/**
	 * @brief Get the second keyboard row.
	 * @param upper Whether to return shift/uppercase keys.
	 * @param alt Whether to return alt keys.
	 * @return A list of characters to display as keyboard buttons.
	 */
	virtual const char *row2(bool upper, bool alt) const = 0;

	/**
	 * @brief Get the third keyboard row.
	 * @param upper Whether to return shift/uppercase keys.
	 * @param alt Whether to return alt keys.
	 * @return A list of characters to display as keyboard buttons.
	 */
	virtual const char *row3(bool upper, bool alt) const = 0;
};

} // namespace layout
} // namespace ui
