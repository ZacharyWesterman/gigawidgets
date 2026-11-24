#include "src/ui.hpp"
#include "src/ui/keyboard_layout/qwerty.hpp"
#include <Fonts/FreeSansBold12pt7b.h>

constexpr const auto KEYBOARD_BUTTONS = ui::color(.75, .75, 1);
constexpr const auto KEYBOARD_BACKGROUND = ui::color(.5, .5, .75);
constexpr const auto KEYBOARD_TEXT = ui::COLOR_BLACK;
#define FONT FreeSansBold12pt7b

void setup() {
	ui::setRotation(ui::ROT_90_DEG);

	auto column = new ui::Column({100_vw, 100_vh});

	auto input = new ui::Input(FONT, ui::COLOR_BLACK, ui::COLOR_WHITE, {2.6_cm, 0.5_cm}, 5_px);

	auto keyboard = new ui::Keyboard(	 //
		ui::layout::qwerty,				 //
		KEYBOARD_TEXT,					 //
		KEYBOARD_BUTTONS,				 //
		KEYBOARD_BACKGROUND,			 //
		{2.5_cm, 4_cm},					 // size
		5_px,							 // border radius
		{0, 0},							 // position
		{ui::ALIGN_LEFT, ui::ALIGN_TOP}, // alignment in parent
		{5_px}							 // padding
	);

	column->push(input);
	column->push(keyboard);

	input->onpress([input](const ui::Event &event) { input->setCursor(input->nearestCursor(event.points[0])); });

	keyboard->onchange([input](char c) { input->insert(c); });
	keyboard->onback([input]() { input->backspace(); });
	keyboard->onsubmit([input]() {
		Serial.println(input->getText());
		input->setText("");
	});

	ui::setRoot(new ui::Body(column));
}

void loop() {
	ui::render();
}
