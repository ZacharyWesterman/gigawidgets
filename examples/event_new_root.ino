// Set a completely new root node on arbitrary click events.
// Previously, this would cause a segfault.

#include "src/ui.hpp"

void setup() {
	auto text = new ui::Text("Sample Text", 3);
	auto body = new ui::Body(text);

	body->onclick([]() {
		auto text = new ui::Text("Text2", 4);
		auto body = new ui::Body(text, ui::COLOR_RED);
		ui::setRoot(body);

		body->onclick([]() {
			auto text = new ui::Text("A", 7);
			auto body = new ui::Body(text, ui::COLOR_GREEN);
			ui::setRoot(body);
		});
	});

	ui::setRoot(body);
}

void loop() {
	ui::render();
}
