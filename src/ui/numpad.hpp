/// @file numpad.hpp
#pragma once

#include <gfxfont.h>

#include "core/color.hpp"
#include "core/fontsize.hpp"
#include "panel.hpp"
#include "text.hpp"

namespace ui {

/**
 * @brief A virtual numpad input widget.
 *
 * This widget renders as a panel containing buttons.
 */
class Numpad : public Panel {
	const GFXfont *font;
	color_t textColor;
	color_t buttonColor;
	std::function<void(char)> insert_handler;
	std::function<void()> backspace_handler;
	std::function<void()> submit_handler;

	void build(const Size &size, std::function<Text *(char, color_t)> maketext);
	void bind(Panel *button);

public:
	/**
	 * @brief Construct numpad with text rendered in the built-in font.
	 * @param textColor The text color.
	 * @param buttonColor The button color.
	 * @param backgroundColor The background color.
	 * @param size The minimum size of the panel. It may expand to fit the child widget.
	 * @param borderRadius The radius of the rounded parts of the panel.
	 * @param pos The position of the panel relative to its parent.
	 * @param align The alignment of the panel relative to its parent.
	 * @param padding The padding to apply to the child widget.
	 */
	Numpad(color_t textColor, color_t buttonColor, color_t backgroundColor, const Size &size = {0, 0}, radius_t borderRadius = 0, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	/**
	 * @brief Construct numpad with text rendered in the given font.
	 * @param font The font to render text in.
	 * @param textColor The text color.
	 * @param buttonColor The button color.
	 * @param backgroundColor The background color.
	 * @param size The minimum size of the panel. It may expand to fit the child widget.
	 * @param borderRadius The radius of the rounded parts of the panel.
	 * @param pos The position of the panel relative to its parent.
	 * @param align The alignment of the panel relative to its parent.
	 * @param padding The padding to apply to the child widget.
	 */
	Numpad(const GFXfont &font, color_t textColor, color_t buttonColor, color_t backgroundColor, const Size &size = {0, 0}, radius_t borderRadius = 0, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

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
};

} // namespace ui
