#include <cstring>

#include "column.hpp"
#include "core/display.hpp"
#include "core/units.hpp"
#include "keyboard.hpp"
#include "panel.hpp"
#include "row.hpp"
#include "text.hpp"

namespace ui {

Keyboard::Keyboard(const layout::KeyboardLayout &layout, color_t textColor, color_t buttonColor, color_t backgroundColor) : layout(&layout), font(nullptr), textColor(textColor), buttonColor(buttonColor), backgroundColor(backgroundColor), Panel(nullptr, backgroundColor, {0, 0}, 0, {0, 0}, {ALIGN_CENTER, ALIGN_BOTTOM}, {0, 5_px}) {
	rebuild([](char letter, color_t color) { return new Text(String(letter), 3, color, {0, 0}, {ALIGN_CENTER, ALIGN_CENTER}); });
}

Keyboard::Keyboard(const layout::KeyboardLayout &layout, const GFXfont &font, color_t textColor, color_t buttonColor, color_t backgroundColor) : layout(&layout), font(&font), textColor(textColor), buttonColor(buttonColor), backgroundColor(backgroundColor), Panel(nullptr, backgroundColor, {0, 0}, 0, {0, 0}, {ALIGN_CENTER, ALIGN_BOTTOM}, {0, 5_px}) {
	rebuild([&font, textColor](char letter, color_t color) { return new Text(String(letter), font, textColor, {0, 0}, {ALIGN_CENTER, ALIGN_CENTER}); });
}

void Keyboard::rebuild(std::function<Text *(char, color_t)> makeText) {
	const auto width = ui::width();
	const auto height = ui::height() * 2 / 3;

	auto column = new Column(Size{width, height}, {0, 0}, {ALIGN_CENTER, ALIGN_TOP}, {0, 0});
	setChild(column);

	const auto buttonWidth = std::min(60, width / 11 - 2);
	const int buttonHeight = std::min(60, height / 4);

	// First row doesn't have any special buttons, just spread it out in the middle
	auto rowText = layout->row1(shift, alt);
	int ct = strlen(rowText);
	auto rowWidth = (buttonWidth + 5) * ct + 5;

	auto row = new Row({rowWidth, buttonHeight + 5}, {0, 0}, {ALIGN_CENTER, ALIGN_TOP}, {2_px, 0, 3_px, 0});
	column->push(row);

	for (int i = 0; i < ct; i++) {
		auto button = new Panel(makeText(rowText[i], textColor), buttonColor, {buttonWidth, buttonHeight}, 5_px);
		row->push(button);
		bind(button);
	}

	// Second row doesn't have any special buttons, just spread it out in the middle
	rowText = layout->row2(shift, alt);
	ct = strlen(rowText);

	row = new Row({(buttonWidth + 5) * ct + 5, buttonHeight + 5}, {0, 0}, {ALIGN_CENTER, ALIGN_TOP}, {2_px, 0, 3_px, 0});
	column->push(row);

	for (int i = 0; i < ct; i++) {
		auto button = new Panel(makeText(rowText[i], textColor), buttonColor, {buttonWidth, buttonHeight}, 5_px);
		row->push(button);
		bind(button);
	}

	// Third row has special buttons, SHIFT and BACKSPACE
	rowText = layout->row3(shift, alt);
	ct = strlen(rowText);

	row = new Row({rowWidth, buttonHeight + 5}, {0, 0}, {ALIGN_CENTER, ALIGN_TOP}, {2_px, 0, 3_px, 0});
	column->push(row);

	auto shiftButton = new Panel(new Text("Shift", 2, textColor, {0, 0}, {ALIGN_CENTER, ALIGN_CENTER}), buttonColor, {buttonWidth * 1.5 + 2, buttonHeight}, 5_px);
	auto backspaceButton = new Panel(new Text("Back", 2, textColor, {0, 0}, {ALIGN_CENTER, ALIGN_CENTER}), buttonColor, {buttonWidth * 1.5 + 3, buttonHeight}, 5_px);
	bind(shiftButton);
	bind(backspaceButton);

	row->push(shiftButton);
	for (int i = 0; i < ct; i++) {
		auto button = new Panel(makeText(rowText[i], textColor), buttonColor, {buttonWidth, buttonHeight}, 5_px);
		row->push(button);
		bind(button);
	}
	row->push(backspaceButton);

	// Fourth row is mostly special buttons.
	// ALT, comma, SPACE, dot, ENTER

	row = new Row({rowWidth, buttonHeight + 5}, {0, 0}, {ALIGN_CENTER, ALIGN_TOP}, {2_px, 0, 3_px, 0});
	column->push(row);

	auto altButton = new Panel(new Text("Alt", 2, textColor, {0, 0}, {ALIGN_CENTER, ALIGN_CENTER}), buttonColor, {buttonWidth * 1.5 + 2, buttonHeight}, 5_px);
	auto commaButton = new Panel(makeText(',', textColor), buttonColor, {buttonWidth, buttonHeight}, 5_px);
	auto spaceButton = new Panel(new Text("Space", 2, textColor, {0, 0}, {ALIGN_CENTER, ALIGN_CENTER}), buttonColor, {buttonWidth * 5 + 20, buttonHeight}, 5_px);
	auto periodButton = new Panel(makeText('.', textColor), buttonColor, {buttonWidth, buttonHeight}, 5_px);
	auto enterButton = new Panel(new Text("Enter", 2, textColor, {0, 0}, {ALIGN_CENTER, ALIGN_CENTER}), buttonColor, {buttonWidth * 1.5 + 2, buttonHeight}, 5_px);
	bind(altButton);
	bind(commaButton);
	bind(spaceButton);
	bind(periodButton);
	bind(enterButton);

	row->push(altButton);
	row->push(commaButton);
	row->push(spaceButton);
	row->push(periodButton);
	row->push(enterButton);
}

void Keyboard::bind(Panel *button) {
	button->onpress([](Panel &btn) { btn.setColor(COLOR_WHITE); });
	button->onblur([this](Panel &btn) { btn.setColor(buttonColor); });
}

} // namespace ui
