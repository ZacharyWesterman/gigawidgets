/// @file keyboard.hpp
#pragma once

#include <gfxfont.h>

#include "core/color.hpp"
#include "core/fontsize.hpp"
#include "keyboard_layout.hpp"
#include "panel.hpp"
#include "text.hpp"

namespace ui {

/**
 * @brief A virtual keyboard input widget.
 *
 * This widget renders as a panel containing buttons and a text input widget.
 */
class Keyboard : public Panel {
	const layout::KeyboardLayout *layout;
	const GFXfont *font;
	color_t textColor;
	color_t buttonColor;
	color_t backgroundColor;
	bool shift = false;
	bool alt = false;
	std::function<void(char)> insert_handler;
	std::function<void()> alt_handler;
	std::function<void()> shift_handler;
	std::function<void()> backspace_handler;
	std::function<void()> submit_handler;

	void rebuild(std::function<Text *(char, color_t)> maketext);
	void bind(Panel *button);

public:
	/**
	 * @brief Construct keyboard with text rendered in the built-in font.
	 * @param layout The keyboard layout, e.g. "qwerty".
	 * @param textColor The text color.
	 * @param buttonColor The button color.
	 * @param backgroundColor The background color.
	 */
	Keyboard(const layout::KeyboardLayout &layout, color_t textColor, color_t buttonColor, color_t backgroundColor);

	/**
	 * @brief Construct keyboard with text rendered in the given font.
	 * @param layout The keyboard layout, e.g. "qwerty".
	 * @param font The font to render text in.
	 * @param textColor The text color.
	 * @param buttonColor The button color.
	 * @param backgroundColor The background color.
	 */
	Keyboard(const layout::KeyboardLayout &layout, const GFXfont &font, color_t textColor, color_t buttonColor, color_t backgroundColor);

	/**
	 * @brief Set the function to be called when a character button is pressed.
	 * @param func The function to call.
	 */
	inline void onchange(std::function<void(char)> func) {
		insert_handler = func;
	}

	/**
	 * @brief Set the function to be called when the backspace button is pressed.
	 * @param func The function to call.
	 */
	inline void onback(std::function<void()> func) {
		backspace_handler = func;
	}

	/**
	 * @brief Set the function to be called when the enter button is pressed.
	 * @param func The function to call.
	 */
	inline void onsubmit(std::function<void()> func) {
		submit_handler = func;
	}

	/**
	 * @brief Set the function to be called when the shift button is pressed.
	 * @param func The function to call.
	 */
	inline void onshift(std::function<void()> func) {
		shift_handler = func;
	}

	/**
	 * @brief Set the function to be called when the alt button is pressed.
	 * @param func The function to call.
	 */
	inline void onalt(std::function<void()> func) {
		alt_handler = func;
	}
};

} // namespace ui
