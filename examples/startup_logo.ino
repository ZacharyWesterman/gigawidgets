#include "src/ui.hpp"
#include "src/ui/icons/skrunk.hpp"
#include "src/ui/shaders/animated/startup_rainbow.hpp"

void setup() {
	ui::setRotation(ui::ROT_270_DEG);

	ui::Position position = {0.5, 0.5};
	ui::Alignment alignment = {ui::ALIGN_CENTER, ui::ALIGN_CENTER};

	auto image = new ui::Image(&ui::icon::skrunk, position, alignment);
	auto body = new ui::Body(image, ui::COLOR_BLACK);
	ui::setRoot(body);

	image->setShader(ui::shader::startupRainbow);
}

void loop() {
	ui::render();
}
