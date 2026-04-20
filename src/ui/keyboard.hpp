/// @file keyboard.hpp
#pragma once

#include <gfxfont.h>

#include "core/color.hpp"
#include "core/fontsize.hpp"
#include "keyboard_layout.hpp"
#include "panel.hpp"

namespace ui {

/**
 * @brief A virtual keyboard input widget.
 *
 * This widget renders as a panel containing buttons and a text input widget.
 */
class Keyboard : public Panel {
	const layout::KeyboardLayout *layout;

public:
	/**
	 * @brief Construct keyboard with text rendered in the built-in font.
	 * @param layout The keyboard layout, e.g. "qwerty".
	 * @param scale A scaling factor for the text, e.g. 2x, 3x etc.
	 * @param textColor The text color.
	 * @param buttonColor The button color.
	 * @param backgroundColor The background color.
	 */
	Keyboard(const layout::KeyboardLayout &layout, fontsize_t scale, color_t textColor, color_t buttonColor, color_t backgroundColor);

	/**
	 * @brief Construct keyboard with text rendered in the given font.
	 * @param layout The keyboard layout, e.g. "qwerty".
	 * @param font The font to render text in.
	 * @param textColor The text color.
	 * @param buttonColor The button color.
	 * @param backgroundColor The background color.
	 */
	Keyboard(const layout::KeyboardLayout &layout, const GFXfont &font, color_t textColor, color_t buttonColor, color_t backgroundColor);
};

} // namespace ui
