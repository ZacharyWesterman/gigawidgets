/// @file input.hpp
#pragma once

#include "panel.hpp"
#include "text.hpp"

namespace ui {

class Input : public Panel {
	int cursor;

public:
	Input(fontsize_t scale, color_t textColor, color_t backgroundColor, const Size &size = {0}, radius_t borderRadius = 0, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	Input(const GFXfont *font, color_t textColor, color_t backgroundColor, const Size &size = {0}, radius_t borderRadius = 0, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	void setText(const String &text);
	const String &getText() const;

	void insert(char c);
	int getCursor() const;
	void setCursor(int index);

	void draw() const override;

	DERIVE_EVENT_HANDLERS(Input)
};

} // namespace ui
