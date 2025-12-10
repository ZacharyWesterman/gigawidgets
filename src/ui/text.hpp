#pragma once

#include <Arduino.h>
#include <gfxfont.h>

#include "core/alignment.hpp"
#include "core/color.hpp"
#include "core/fontsize.hpp"
#include "core/position.hpp"
#include "core/widget.hpp"

namespace ui {

class Text : public Widget {
protected:
	const GFXfont *font;
	String text;
	fontsize_t scale;
	color_t textColor;
	bool wrap;

public:
	Text(const String &text, fontsize_t scale = 1, color_t color = COLOR_WHITE, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, bool wrap = true);

	Text(const String &text, const GFXfont *font, color_t color = COLOR_WHITE, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, bool wrap = true);

	void draw() const override;
	Size size() const override;

	void setText(const String &text);
	void setWrap(bool wrap);
	void setFont(GFXfont *const font);
	void setScale(fontsize_t scale);
};

} // namespace ui
