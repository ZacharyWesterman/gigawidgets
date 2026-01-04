// When a point on the parent widget is held, snap the child widget to that point.
// The child widget does not instantly teleport, instead it moves over a short time frame.

#include "src/ui.hpp"
#include "src/ui/icons/firefox.hpp"

void setup() {
	// Create a simple UI; just a Body containing an Image.

	ui::setRotation(ui::ROT_270_DEG);

	ui::Position position = {0, 0};
	ui::Alignment alignment = {ui::ALIGN_CENTER, ui::ALIGN_CENTER};

	auto image = new ui::Image(&ui::icon::firefox, position, alignment);
	auto body = new ui::Body(image, ui::COLOR_BLACK);
	ui::setRoot(body);

	// When the Body is pressed and held for a bit,
	body->onhold([image](const ui::Event &event) {
		auto oldPos = image->getPosition();
		auto targetPos = event.coords[0];

		// Move to halfway between current and target position
		ui::Position newPos = {
			(oldPos.x + targetPos.x - 0.5) / 2,
			(oldPos.y + targetPos.y - 0.5) / 2,
		};

		image->setPosition(newPos);
	});
}

void loop() {
	ui::render();
}
