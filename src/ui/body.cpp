#include <Arduino.h>

#include "body.hpp"
#include "core/display.hpp"

namespace ui {

Body::Body(Widget *const child, color_t backgroundColor, const Padding &padding) : backgroundColor(backgroundColor), SingleChildWidget(child, {0, 0}, {ALIGN_LEFT, ALIGN_TOP}, padding) {}

void Body::draw() const {
	if (child->redrawRequested() || redrawSelf || rotationChanged()) {
		// Requires a full re-render
		fillScreen(backgroundColor);
	}
	child->draw();
}

Size Body::size() const {
	return {width(), height()};
}

Bounds Body::bounds() const {
	return {
		{0, 0},
		{width(), height()},
	};
}

void Body::setColor(color_t new_color) {
	backgroundColor = new_color;
	redrawSelf = true;
}

} // namespace ui
