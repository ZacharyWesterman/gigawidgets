#include "panel.hpp"
#include "core/display.hpp"

#include <Arduino.h>

namespace ui {

Panel::Panel(Widget *child, color_t color, const Size &size, radius_t borderRadius, const Position &pos, const Alignment &align, const Padding &padding) : color(color), panelSize(size), borderRadius(borderRadius), SingleChildWidget(child, pos, align, padding) {}

void Panel::draw() const {
	// if (child->redrawRequested() || redrawSelf || redrawParent || rotationChanged()) {
	const auto b = bounds();
	fillRoundRect(b.min.x, b.min.y, b.max.x - b.min.x, b.max.y - b.min.y, borderRadius, color);
	// }
	child->draw();
	Serial.println("draw");
}

bool Panel::update(time_t time_ms) {
	return SingleChildWidget::update(time_ms) || redrawSelf;
}

void Panel::drawDone() {
	redrawSelf = false;
	redrawParent = false;
	child->drawDone();
}

Size Panel::size() const {
	const auto childSize = child->size();

	uisize_t xmin = childSize.x + padding.left + padding.right;
	uisize_t ymin = childSize.y + padding.top + padding.bottom;

	return {
		std::max(xmin, panelSize.x),
		std::max(ymin, panelSize.y),
	};
}

void Panel::setColor(color_t new_color) {
	color = new_color;
	redrawSelf = true;
}

color_t Panel::getColor() const {
	return color;
}

void Panel::setBorderRadius(radius_t new_radius) {
	borderRadius = new_radius;
	redrawParent = true;
}

} // namespace ui
