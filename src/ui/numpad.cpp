#include <cstring>

#include "column.hpp"
#include "core/display.hpp"
#include "core/units.hpp"
#include "numpad.hpp"
#include "panel.hpp"
#include "row.hpp"
#include "text.hpp"

namespace ui {

Numpad::Numpad(color_t textColor, color_t buttonColor, color_t backgroundColor, const Size &size, radius_t borderRadius, const Position &pos, const Alignment &align, const Padding &padding) : font(nullptr), textColor(textColor), buttonColor(buttonColor), Panel(nullptr, backgroundColor, size, borderRadius, pos, align, padding) {
	build(size, [](char letter, color_t color) { return new Text(String(letter), 3, color, {0, 0}, {ALIGN_CENTER, ALIGN_CENTER}); });
}

Numpad::Numpad(const GFXfont &font, color_t textColor, color_t buttonColor, color_t backgroundColor, const Size &size, radius_t borderRadius, const Position &pos, const Alignment &align, const Padding &padding) : font(&font), textColor(textColor), buttonColor(buttonColor), Panel(nullptr, backgroundColor, size, borderRadius, pos, align, padding) {
	build(size, [&font](char letter, color_t color) { return new Text(String(letter), font, color, {0, 0}, {ALIGN_CENTER, ALIGN_CENTER}); });
}

void Numpad::build(const Size &size, std::function<Text *(char, color_t)> maketext) {
	auto column = new Column(size, {0, 0}, {ALIGN_CENTER, ALIGN_TOP}, {0, 0});
	setChild(column);

	const auto buttonWidth = std::min(60, size.x / 3 - 2);
	const int buttonHeight = std::min(60, size.y / 5 - 5);

	// First row - 7 8 9
	auto rowWidth = (buttonWidth + 5) * 3 + 5;
	auto row = new Row({rowWidth, buttonHeight + 5}, {0, 0}, {ALIGN_CENTER, ALIGN_TOP}, {2_px, 0, 3_px, 0});
	column->push(row);
	for (char i = '7'; i <= '9'; i++) {
		auto button = new Panel(maketext(i, textColor), buttonColor, {buttonWidth, buttonHeight}, 5_px);
		row->push(button);
		bind(button);
		button->onrelease([this, i]() {
			if (insert_handler) {
				insert_handler(i);
			}
		});
	}

	// Second row - 4 5 6
	row = new Row({rowWidth, buttonHeight + 5}, {0, 0}, {ALIGN_CENTER, ALIGN_TOP}, {2_px, 0, 3_px, 0});
	column->push(row);
	for (char i = '4'; i <= '6'; i++) {
		auto button = new Panel(maketext(i, textColor), buttonColor, {buttonWidth, buttonHeight}, 5_px);
		row->push(button);
		bind(button);
		button->onrelease([this, i]() {
			if (insert_handler) {
				insert_handler(i);
			}
		});
	}

	// Third row - 1 2 3
	row = new Row({rowWidth, buttonHeight + 5}, {0, 0}, {ALIGN_CENTER, ALIGN_TOP}, {2_px, 0, 3_px, 0});
	column->push(row);
	for (char i = '1'; i <= '3'; i++) {
		auto button = new Panel(maketext(i, textColor), buttonColor, {buttonWidth, buttonHeight}, 5_px);
		row->push(button);
		bind(button);
		button->onrelease([this, i]() {
			if (insert_handler) {
				insert_handler(i);
			}
		});
	}

	// Fourth row has special buttons, '-', '0', '.'
	row = new Row({rowWidth, buttonHeight + 5}, {0, 0}, {ALIGN_CENTER, ALIGN_TOP}, {2_px, 0, 3_px, 0});
	column->push(row);
	const auto letters = "-0.";
	for (int i = 0; i < 3; i++) {
		char c = letters[i];
		auto button = new Panel(maketext(c, textColor), buttonColor, {buttonWidth, buttonHeight}, 5_px);
		row->push(button);
		bind(button);
		button->onrelease([this, c]() {
			if (insert_handler) {
				insert_handler(c);
			}
		});
	}

	// Fifth row is two special buttons - Back Enter
	row = new Row({rowWidth, buttonHeight + 5}, {0, 0}, {ALIGN_CENTER, ALIGN_TOP}, {2_px, 0, 3_px, 0});
	const auto text_with_font = [this](const char *text) -> Text * { return new Text(text, *font, textColor, {0, 0}, {ALIGN_CENTER, ALIGN_CENTER}); };
	const auto text_without_font = [this](const char *text) -> Text * { return new Text(text, 2, textColor, {0, 0}, {ALIGN_CENTER, ALIGN_CENTER}); };

	column->push(row);
	auto backButton = new Panel(font ? text_with_font("Back") : text_without_font("Back"), buttonColor, {buttonWidth * 1.5 + 2, buttonHeight}, 5_px);
	auto enterButton = new Panel(font ? text_with_font("Enter") : text_without_font("Enter"), buttonColor, {buttonWidth * 1.5 + 2, buttonHeight}, 5_px);
	backButton->onrelease([this]() {
		if (backspace_handler) {
			backspace_handler();
		}
	});
	enterButton->onrelease([this]() {
		if (submit_handler) {
			submit_handler();
		}
	});
	bind(backButton);
	bind(enterButton);
	row->push(backButton);
	row->push(enterButton);
}

void Numpad::bind(Panel *button) {
	button->onpress([this](Panel &btn) { btn.setColor(COLOR_WHITE); });
	button->onblur([this](Panel &btn) { btn.setColor(buttonColor); });
}

} // namespace ui
