#include "src/ui.hpp"

void setup() {
	ui::setRotation(ui::ROT_90_DEG);

	auto keyboard = new ui::Keyboard(4, ui::COLOR_BLACK, ui::color(.75, .75, 1), ui::color(.5, .5, .75));
	auto body = new ui::Body(keyboard);

	ui::setRoot(body);
}

void loop() {
	ui::render();
}
