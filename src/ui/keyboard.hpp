/// @file keyboard.hpp
#pragma once

#include <gfxfont.h>

#include "core/color.hpp"
#include "core/fontsize.hpp"
#include "panel.hpp"

namespace ui {

/**
 * @brief A virtual keyboard input widget.
 *
 * This widget renders as a panel containing buttons and a text input widget.
 */
class Keyboard : public Panel {
public:
	/**
	 * @brief Construct keyboard with text rendered in the built-in font.
	 * @param scale A scaling factor for the text, e.g. 2x, 3x etc.
	 * @param textColor The text color.
	 * @param buttonColor The button color.
	 * @param backgroundColor The background color.
	 */
	Keyboard(fontsize_t scale, color_t textColor, color_t buttonColor, color_t backgroundColor);

	/**
	 * @brief Construct keyboard with text rendered in the given font.
	 * @param font The font to render text in.
	 * @param textColor The text color.
	 * @param buttonColor The button color.
	 * @param backgroundColor The background color.
	 */
	Keyboard(const GFXfont *font, color_t textColor, color_t buttonColor, color_t backgroundColor);

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
	 * @param newColor The new text color.
	 */
	void setTextColor(color_t newColor);

	/**
	 * @brief Set the button color.
	 * @param newColor The new button color.
	 */
	void setButtonColor(color_t newColor);

	/**
	 * @brief Set the background color.
	 * @param newColor The new background color.
	 */
	void setBackgroundColor(color_t newColor);
};

} // namespace ui
