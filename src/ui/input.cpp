#include "input.hpp"
#include "../ui.hpp"
#include "core/display.hpp"

namespace ui {

Input::Input(fontsize_t scale, color_t textColor, color_t backgroundColor, const Size &size, radius_t borderRadius, const Position &pos, const Alignment &align, const Padding &padding) : Panel(new Text("", scale, textColor, {0, 0}, {ALIGN_LEFT, ALIGN_CENTER}, false), backgroundColor, size, borderRadius, pos, align, padding), cursor(0), lastRender(0), showCursor(true) {}

Input::Input(const GFXfont *font, color_t textColor, color_t backgroundColor, const Size &size, radius_t borderRadius, const Position &pos, const Alignment &align, const Padding &padding) : Panel(new Text("", font, textColor, {0, 0}, {ALIGN_LEFT, ALIGN_CENTER}, false), backgroundColor, size, borderRadius, pos, align, padding), cursor(0), lastRender(0), showCursor(true) {}

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
	lastRender = millis();
	redrawSelf = true;
	showCursor = true;
	endWrite();
	draw();
}

int Input::nearestCursor(const Coords &coords) const {
	auto child = reinterpret_cast<Text *>(getChild());
	const auto bounds_x = child->bounds().min.x;
	if (coords.x <= bounds_x) {
		return 0;
	}

	const int len = child->getText().length();
	const auto x = coords.x - bounds_x;

	int prevPos = 0;
	int pos = 0;

	// Not at all efficient but it works for now.
	// In most cases, text will not be long enough to warrant something like binary search.
	for (int i = 0; i <= len; i++) {
		pos = child->getWidthAtChar(i);
		if (prevPos <= x && pos >= x) {
			// Shift to whichever side of the character the x coord was closest to.
			return (x - prevPos > pos - x) ? i : i - 1;
		}
		prevPos = pos;
	}

	return len;
}

void Input::draw() const {
	Panel::draw();
	if (showCursor) {
		drawCursor();
	}
}

bool Input::update(time_t time) {
	const bool updated = Panel::update(time);
	redrawSelf = child->redrawRequested();

	if (time - lastRender >= 500) {
		// Update the cursor, but don't force
		// the child or parent widgets to re-render.
		lastRender = time;
		showCursor = !showCursor;
		redrawSelf = true;
	}

	return updated || redrawSelf;
}

void Input::drawCursor() const {
	auto child = reinterpret_cast<Text *>(getChild());
	auto width = child->getWidthAtChar(cursor);

	auto b = child->bounds();

	// Coords for the center bar
	uisize_t x = b.min.x + width;
	uisize_t y = b.min.y + 2;
	uisize_t h = b.max.y - b.min.y - 2;
	color_t color = ~getColor();

	// Coords for the serifs
	uisize_t serif_x = x - 3;
	uisize_t serif_w = 7;
	uisize_t y1 = y + h;

	// Draw the cursor in a sort of I shape.
	ui::drawFastVLine(x, y, h, color);
	ui::drawFastVLine(x + 1, y, h, color);

	ui::drawFastHLine(serif_x, y - 1, serif_w, color);
	ui::drawFastHLine(serif_x, y, serif_w, color);
	ui::drawFastHLine(serif_x, y1 - 1, serif_w, color);
	ui::drawFastHLine(serif_x, y1, serif_w, color);
}

} // namespace ui
