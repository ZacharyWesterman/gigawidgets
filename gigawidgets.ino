#include "src/ui.hpp"
#include "src/ui/icons/firefox.hpp"
#include "src/ui/icons/skrunk.hpp"
#include <Fonts/FreeSerif18pt7b.h>

// void setup() {
// 	// Serial.begin(9600);
// 	// while (!Serial)
// 	// 	;

// 	ui::setRotation(ui::ROT_90_DEG);

// 	// Position is relative to parent.
// 	ui::Position position = {0, 0};
// 	// Alignment is relative to position on parent.
// 	ui::Alignment alignment = {ui::ALIGN_LEFT, ui::ALIGN_TOP};
// 	// Padding can be in px, mm, cm, in, vw, or vh.
// 	ui::Padding padding = {10_px};
// 	// Size is absolute
// 	ui::Size size = {ui::width(), ui::height()};

// 	// Build the UI

// 	auto column = new ui::Column(size, position, alignment, padding);
// 	// column->setChildAlign(ui::ALIGN_BOTTOM);

// 	column->push(new ui::Text("This is line 1.", &FreeSerif18pt7b, ui::COLOR_LIGHT_YELLOW));
// 	column->push(new ui::Text("This is line 2.", &FreeSerif18pt7b, ui::COLOR_LIGHT_BLUE));
// 	column->push(new ui::Image(&ui::icon::firefox));
// 	column->push(new ui::Text("This is line 3.", &FreeSerif18pt7b, ui::COLOR_ORANGE));
// 	column->push(new ui::Text("This is line 4.", &FreeSerif18pt7b, ui::COLOR_PINK, {.99f, 0.f}, {ui::ALIGN_RIGHT, ui::ALIGN_TOP}));
// 	column->push(new ui::Text("This is line 5.", &FreeSerif18pt7b, ui::COLOR_YELLOW));

// 	// Toggle the child alignment when clicked.
// 	column->onclick([column]() { column->setChildAlign(column->getChildAlign() == ui::ALIGN_TOP ? ui::ALIGN_BOTTOM : ui::ALIGN_TOP); });

// 	auto body = new ui::Body(column, ui::COLOR_BLACK);
// 	ui::setRoot(body);
// }

// void loop() {
// 	ui::render();
// }

void setup() {
	//
	ui::drawPixel(10, 10, ui::COLOR_RED);
}

void loop() {
	ui::render();
}
