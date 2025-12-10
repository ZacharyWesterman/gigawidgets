#include "text.hpp"
#include "core/display.hpp"

#include <Adafruit_GFX.h>

namespace ui {

Text::Text(const String &text, const GFXfont *font, color_t color, const Position &pos, const Alignment &align, bool wrap) : text(text), font(font), scale(1), textColor(color), wrap(wrap), Widget(pos, align) {}

Text::Text(const String &text, fontsize_t scale, color_t color, const Position &pos, const Alignment &align, bool wrap) : text(text), font(nullptr), scale(scale), textColor(color), wrap(wrap), Widget(pos, align) {}

void Text::draw() const {
	// Create a canvas in memory so that text doesn't go outside the bounds of its parent.

	const auto b = bounds();
	const auto p = parentBounds();

	const auto width = p.max.x - p.min.x;
	const auto height = p.max.y - p.min.y;

	const uint8_t y_offset = font ? font->yAdvance / 2 : 0;

	GFXcanvas1 canvas(width, height);
	canvas.setCursor(b.min.x - p.min.x, b.min.y - p.min.y + y_offset);
	canvas.setTextSize(scale);
	canvas.setTextColor(textColor);
	canvas.setTextWrap(wrap);
	canvas.setFont(font);

	canvas.print(text);

	// Copy the canvas onto the screen.
	ui::drawBitmap(p.min.x, p.min.y, canvas.getBuffer(), width, height, textColor);
}

Size Text::size() const {
	return {0, 0};
}

void Text::setText(const String &text) {
	this->text = text;
	redrawParent = true;
}

void Text::setWrap(bool wrap) {
	this->wrap = wrap;
	redrawParent = true;
}

void Text::setFont(GFXfont *const font) {
	this->wrap = font;
	redrawParent = true;
}

void Text::setScale(fontsize_t scale) {
	this->scale = scale;
	redrawParent = true;
}

} // namespace ui
