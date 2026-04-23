#include "box.hpp"
#include <Arduino.h>

namespace ui {

Box::Box(Widget *child, const Bounds &bounds) : widgetBounds(bounds), SingleChildWidget(child) {}

Bounds Box::bounds() const {
	Coords min = parentBounds().min;
	Coords max = {
		widgetBounds.max.x - widgetBounds.min.x + min.x,
		widgetBounds.max.y - widgetBounds.min.y + min.y,
	};

	return {min, max};
}

void Box::setBounds(const Bounds &bounds) {
	widgetBounds = bounds;
	Serial.print(bounds.min.x);
	Serial.print(',');
	Serial.print(bounds.min.y);
	Serial.print(' ');
	Serial.print(bounds.max.x);
	Serial.print(',');
	Serial.print(bounds.max.y);
	Serial.println(';');
}

void Box::draw() const {
	child->draw();
}

} // namespace ui
