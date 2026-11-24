#include "src/ui.hpp"
#include <Fonts/FreeSansBold12pt7b.h>

constexpr const auto NUMPAD_BUTTONS = ui::color(.75, .75, 1);
constexpr const auto NUMPAD_BACKGROUND = ui::color(.5, .5, .75);
constexpr const auto NUMPAD_TEXT = ui::COLOR_BLACK;
#define FONT FreeSansBold12pt7b

void setup() {
	ui::setRotation(ui::ROT_90_DEG);

	auto column = new ui::Column({100_vw, 100_vh});

	auto input = new ui::Input(FONT, ui::COLOR_BLACK, ui::COLOR_WHITE, {3.5_cm, 0.5_cm});

	auto numpad = new ui::Numpad(		 //
		FONT,							 //
		NUMPAD_TEXT,					 //
		NUMPAD_BUTTONS,					 //
		NUMPAD_BACKGROUND,				 //
		{2.5_cm, 4_cm},					 // size
		5_px,							 // border radius
		{0, 0},							 // position
		{ui::ALIGN_LEFT, ui::ALIGN_TOP}, // alignment in parent
		{5_px}							 // padding
	);

	column->push(input);
	column->push(numpad);

	ui::setRoot(new ui::Body(column));
}

void loop() {
	ui::render();
}
