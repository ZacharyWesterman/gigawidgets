#include "src/ui.hpp"
#include "src/ui/icons/firefox.hpp"
#include "src/ui/icons/skrunk.hpp"
#include <Fonts/FreeSerif18pt7b.h>

void setup() {
	ui::setRotation(ui::ROT_270_DEG);

	// Position is relative to parent.
	ui::Position position = {0, 0};
	// Alignment is relative to position on parent.
	ui::Alignment alignment = {ui::ALIGN_LEFT, ui::ALIGN_TOP};
	// Padding can be in px, mm, cm, in, vw, or vh.
	ui::Padding padding = {10_px};
	// Size is absolute
	ui::Size size = {ui::width(), ui::height()};

	// Build the UI

	auto column = new ui::Column(size, position, alignment, padding);

	column->addChild(new ui::Text("This is line 1.", &FreeSerif18pt7b, ui::COLOR_LIGHT_YELLOW));
	column->addChild(new ui::Text("This is line 2.", &FreeSerif18pt7b, ui::COLOR_LIGHT_BLUE));
	column->addChild(new ui::Image(&ui::icon::firefox));
	column->addChild(new ui::Text("This is line 3.", &FreeSerif18pt7b, ui::COLOR_PINK, {.99f, 0.f}, {ui::ALIGN_RIGHT, ui::ALIGN_TOP}));
	column->addChild(new ui::Text("This is line 4.", &FreeSerif18pt7b, ui::COLOR_YELLOW));

	auto body = new ui::Body(column, ui::COLOR_BLACK);
	ui::setRoot(body);
}

void loop() {
	ui::render();
}
