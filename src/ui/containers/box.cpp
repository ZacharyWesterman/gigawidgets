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
	requestParentRedraw();
}

void Box::draw() const {
	// No graphics to draw here.
}

bool Box::update(time_t time_ms) {
	SingleChildWidget::update(time_ms);
	if (redrawSelf) {
		requestParentRedraw();
	}
	return redrawSelf;
}

} // namespace ui
