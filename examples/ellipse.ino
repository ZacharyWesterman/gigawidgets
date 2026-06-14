// Renders an ellipse to the screen that oscillates its radii and cycles through the rainbow.

#include "src/ui.hpp"
#include "src/ui/renderables.hpp"
#include <cmath>

ui::Ellipse shape(ui::COLOR_RED, 1_cm, 2_cm, true);
ui::Image *image = nullptr;

float linear_map(float value, float input_min, float input_max, float output_min, float output_max) {
	return (value - input_min) / (input_max - input_min) * (output_max - output_min) + output_min;
}

void update_radii_every_frame() {
	float seconds = millis() / 500.f;

	// Bounce on it silly style
	shape.radius1 = linear_map(-std::sin(seconds), -1, 1, 1_cm, 1.5_cm);
	shape.radius2 = linear_map(std::sin(seconds), -1, 1, 1_cm, 1.5_cm);

	// Pride month
	shape.color = ui::hsv(seconds * 40, 1.f, 1.f);

	// Immediately draw next frame.
	image->requestParentRedraw();
	ui::setTimeout(update_radii_every_frame, 1);
}

void setup() {
	image = new ui::Image(shape, CENTERED_IN_PARENT);
	auto body = new ui::Body(image, ui::COLOR_BLACK);

	ui::setTimeout(update_radii_every_frame, 1);

	ui::setRoot(body);
}

void loop() {
	ui::render();
}
