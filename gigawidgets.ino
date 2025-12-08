#include "src/ui.hpp"
#include "src/ui/icons/firefox.hpp"
#include "src/ui/shaders/grayscale.hpp"
#include "src/ui/shaders/negative.hpp"

void setup() {
	// Position is relative to parent.
	ui::Position position = {0.5, 0.5};
	// Alignment is relative to position on parent.
	ui::Alignment alignment = {ui::ALIGN_CENTER, ui::ALIGN_CENTER};
	// Padding can be in px, mm, cm, in, vw, or vh.
	ui::Padding padding = {0.5_cm, 0.5_cm};

	ui::setRotation(ui::ROT_270_DEG);

	// Build the UI
	const auto &icon = ui::icon::firefox;
	auto avgColor = icon.averageColor();

	auto image = new ui::Image(&icon, position, alignment);
	auto button = new ui::Button(image, ui::COLOR_GRAY, {.4_in, .4_in}, 20, position, alignment);
	auto body = new ui::Body(button, ui::COLOR_BLACK);
	ui::setRoot(body);

	image->setShader(ui::shader::grayscale);

	// Highlight the button on press, and make icon negative
	button->onpress([=]() {
		button->setColor(ui::COLOR_WHITE);
		image->setShader(ui::shader::negative);
	});
	button->onblur([=]() {
		button->setColor(avgColor);
		image->removeShader();
	});
}

void loop() {
	ui::render();
}
