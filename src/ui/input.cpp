#include "input.hpp"
#include "core/display.hpp"

namespace ui {

Input::Input(fontsize_t scale, color_t textColor, color_t backgroundColor, const Size &size, radius_t borderRadius, const Position &pos, const Alignment &align, const Padding &padding) : Panel(new Text("", scale, textColor, {0, 0}, {ALIGN_LEFT, ALIGN_CENTER}, false), backgroundColor, size, borderRadius, pos, align, padding) {}

Input::Input(const GFXfont *font, color_t textColor, color_t backgroundColor, const Size &size, radius_t borderRadius, const Position &pos, const Alignment &align, const Padding &padding) : Panel(new Text("", font, textColor, {0, 0}, {ALIGN_LEFT, ALIGN_CENTER}, false), backgroundColor, size, borderRadius, pos, align, padding) {}

void Input::setText(const String &text) {
	auto child = reinterpret_cast<Text *>(getChild());
	child->setText(text);
	cursor = text.length();
}

const String &Input::getText() const {
	auto child = reinterpret_cast<Text *>(getChild());
	return child->getText();
}

void Input::insert(char c) {
	auto child = reinterpret_cast<Text *>(getChild());
	auto text = child->getText();

	child->setText(text.substring(0, cursor) + c + text.substring(cursor));
	cursor++;
}

int Input::getCursor() const {
	return cursor;
}

void Input::setCursor(int index) {
	auto child = reinterpret_cast<Text *>(getChild());
	auto text = child->getText();

	cursor = std::min(std::max(0, index), (int)text.length());
	redrawSelf = true;
}

void Input::draw() const {
	Panel::draw();

	auto child = reinterpret_cast<Text *>(getChild());
	auto width = child->getWidthAtChar(cursor);

	auto b = child->bounds();

	ui::drawFastVLine(b.min.x + width, b.min.y, b.max.y - b.min.y, child->getColor());
}

} // namespace ui
