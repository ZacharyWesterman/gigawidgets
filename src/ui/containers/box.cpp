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
	redrawParent = true;
}

void Box::draw() const {
	child->draw();
}

} // namespace ui
