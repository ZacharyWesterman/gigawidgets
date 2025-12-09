#include "text.hpp"
#include "core/display.hpp"

namespace ui {

Text::Text(const String &text, fontsize_t scale, color_t color, const Position &pos, const Alignment &align) : text(text), scale(scale), textColor(color), Widget(pos, align) {}

void Text::draw() const {
	const auto b = bounds();

	ui::setCursor(b.min.x, b.min.y);
	ui::setTextSize(scale);
	ui::setTextColor(textColor);
	ui::setTextWrap(false);
	ui::print(text);
}

Size Text::size() const {
	return {
		text.length() * 6 * scale,
		8 * scale,
	};
}

void Text::setText(const String &text) {
	this->text = text;
	redrawParent = true;
}

} // namespace ui
