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

	void build(const Size &size, std::function<Text *(char, color_t)> maketext);
	void bind(Panel *button);

public:
	/**
	 * @brief Construct numpad with text rendered in the built-in font.
	 * @param textColor The text color.
	 * @param buttonColor The button color.
	 * @param backgroundColor The background color.
	 */
	Numpad(color_t textColor, color_t buttonColor, color_t backgroundColor, const Size &size = {0, 0}, radius_t borderRadius = 0, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	/**
	 * @brief Construct numpad with text rendered in the given font.
	 * @param font The font to render text in.
	 * @param textColor The text color.
	 * @param buttonColor The button color.
	 * @param backgroundColor The background color.
	 */
	Numpad(const GFXfont &font, color_t textColor, color_t buttonColor, color_t backgroundColor, const Size &size = {0, 0}, radius_t borderRadius = 0, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});
};

} // namespace ui
