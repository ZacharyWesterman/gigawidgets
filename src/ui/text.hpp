/// @file text.hpp
#pragma once

#include <Arduino.h>
#include <gfxfont.h>

#include "core/alignment.hpp"
#include "core/color.hpp"
#include "core/fontsize.hpp"
#include "core/position.hpp"
#include "core/widget.hpp"

namespace ui {

/**
 * @brief Display text to the screen.
 */
class Text : public Widget {
protected:
	/// @brief The font to render the text in. If null, defaults to the built-in font.
	const GFXfont *font;
	/// @brief The text to display.
	String text;
	/// @brief A scaling factor for the text, e.g. 2x, 3x, etc.
	fontsize_t scale;
	/// @brief The text color.
	color_t textColor;
	/// @brief If true, wrap the text when reaching the right side of the parent widget. If false, don't wrap, just truncate.
	bool wrap;

public:
	/**
	 * @brief Construct text with the built-in font.
	 * @param text The text to display.
	 * @param scale A scaling factor for the text, e.g. 2x, 3x etc.
	 * @param color The text color.
	 * @param pos The position of the text relative to its parent.
	 * @param align The alignment of the text relative to its parent.
	 * @param wrap If true, wrap the text when reaching the right side of the parent widget. If false, don't wrap, just truncate.
	 */
	Text(const String &text, fontsize_t scale = 1, color_t color = COLOR_WHITE, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, bool wrap = true);

	/**
	 * @brief Construct text with a given font.
	 * @param text The text to display.
	 * @param font The font to render text in.
	 * @param color The text color.
	 * @param pos The position of the text relative to its parent.
	 * @param align The alignment of the text relative to its parent.
	 * @param wrap If true, wrap the text when reaching the right side of the parent widget. If false, don't wrap, just truncate.
	 */
	Text(const String &text, const GFXfont *font, color_t color = COLOR_WHITE, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, bool wrap = true);

	void draw() const override;
	Size size() const override;

	/**
	 * @brief Set the text to display.
	 * @param text The new text to display.
	 */
	void setText(const String &text);

	/**
	 * @brief Set whether text wraps.
	 * @param wrap If true, wrap the text when reaching the right side of the parent widget. If false, don't wrap, just truncate.
	 */
	void setWrap(bool wrap);

	/**
	 * @brief Set the font to render text in.
	 * @param font The new font to render the text in. If null, defaults to the built-in font.
	 */
	void setFont(GFXfont *const font);

	/**
	 * @brief Set the scaling factor for the text.
	 * @param scale The new scaling factor for the text, e.g. 2x, 3x, etc.
	 */
	void setScale(fontsize_t scale);

	/**
	 * @brief Set the text color.
	 * @param new_color The new text color.
	 */
	void setColor(color_t new_color);
};

} // namespace ui
