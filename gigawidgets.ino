#include "src/ui.hpp"
#include "src/ui/icons/skrunk.hpp"
#include <Fonts/FreeSerif18pt7b.h>

void setup() {
	// Position is relative to parent.
	ui::Position position = {0.5, 0.5};
	// Alignment is relative to position on parent.
	ui::Alignment alignment = {ui::ALIGN_CENTER, ui::ALIGN_CENTER};
	// Padding can be in px, mm, cm, in, vw, or vh.
	ui::Padding padding = {0.5_cm};

	ui::setRotation(ui::ROT_270_DEG);

	// Build the UI
	auto text = new ui::Text("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", &FreeSerif18pt7b, ui::COLOR_LIGHT_GREEN);

	auto logo = new ui::Image(&ui::icon::skrunk, position, alignment);

	auto collection = new ui::Collection({ui::width(), ui::height()}, {0, 0}, {ui::ALIGN_LEFT, ui::ALIGN_TOP}, padding);
	collection->addChild(logo);
	collection->addChild(text);

	auto body = new ui::Body(collection, ui::COLOR_BLACK);
	ui::setRoot(body);
}

void loop() {
	ui::render();
}
