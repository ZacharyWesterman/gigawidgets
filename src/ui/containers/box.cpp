#include "box.hpp"
#include <Arduino.h>

namespace ui {

Box::Box(Widget *child, const Bounds &bounds) : widgetBounds(bounds), SingleChildWidget(child) {}

Bounds Box::bounds() const {
	return widgetBounds;
}

void Box::setBounds(const Bounds &bounds) {
	widgetBounds = bounds;
	redrawSelf = true;
	if (parent) {
		parent->requestRedraw();
	}
}

void Box::draw() const {
	// No graphics to draw here.
}

bool Box::update(time_t time_ms) {
	SingleChildWidget::update(time_ms);
	if (redrawSelf && parent) {
		parent->requestRedraw();
	}
	return redrawSelf;
}

} // namespace ui
