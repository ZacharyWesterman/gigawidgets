#include "box.hpp"

namespace ui {

Box::Box(Widget *child, const Bounds &bounds) : widgetBounds(bounds), SingleChildWidget(child) {}

Bounds Box::bounds() const {
	return widgetBounds;
}

void Box::setBounds(const Bounds &bounds) {
	widgetBounds = bounds;
}

void Box::draw() const {
	child->draw();
}

} // namespace ui
