#pragma once

#include <Arduino.h>

#include "core/alignment.hpp"
#include "core/color.hpp"
#include "core/element.hpp"
#include "core/fontsize.hpp"
#include "core/position.hpp"

namespace ui {

class Text : public Element {
protected:
	String text;
	fontsize_t scale;
	color_t textColor;

public:
	Text(const String &text, fontsize_t scale = 1, color_t color = COLOR_WHITE, const Position &pos = {0.5, 0.5}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP});

	virtual void draw() const override;
	virtual Size size() const override;

	void setText(const String &text);
};

} // namespace ui
