#include "src/ui.hpp"
#include "src/ui/icons/skrunk.hpp"
#include "src/ui/shaders/animated/startup_rainbow.hpp"

void setup() {
	// Position is relative to parent.
	ui::Position position = {0.5, 0.5};
	// Alignment is relative to position on parent.
	ui::Alignment alignment = {ui::ALIGN_CENTER, ui::ALIGN_CENTER};
	// Padding can be in px, mm, cm, in, vw, or vh.
	ui::Padding padding = {0.5_cm, 0.5_cm};

	ui::setRotation(ui::ROT_270_DEG);

	// Build the UI
	const auto &icon = ui::icon::skrunk;

	auto image = new ui::Image(&icon, position, alignment);
	auto body = new ui::Body(image, ui::COLOR_BLACK);
	ui::setRoot(body);

	// Flash bright every 1000ms.
	image->setShader(ui::shader::startupRainbow);

	while (millis() < 5000) {
		ui::render();
	}

	ui::setRoot(nullptr);
	ui::setRoot(new ui::Body(new ui::Text("")));
}

void loop() {
	ui::render();
}
