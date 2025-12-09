#include "button.hpp"
#include "core/display.hpp"

namespace ui {

Button::Button(Widget *child, color_t color, const Size &size, radius_t borderRadius, const Position &pos, const Alignment &align, const Padding &padding) : color(color), buttonSize(size), borderRadius(borderRadius), SingleChildElement(child, pos, align, padding) {}

void Button::draw() const {
	if (child->redrawRequested() || redrawSelf || redrawParent || rotationChanged()) {
		const auto b = bounds();
		fillRoundRect(b.min.x, b.min.y, b.max.x - b.min.x, b.max.y - b.min.y, borderRadius, color);
	}
	child->draw();
}

bool Button::update(time_t time_ms) {
	return SingleChildElement::update(time_ms) || redrawSelf;
}

void Button::drawDone() {
	redrawSelf = false;
	redrawParent = false;
	child->drawDone();
}

Size Button::size() const {
	const auto childSize = child->size();

	return {
		max(childSize.x + padding.left + padding.right, buttonSize.x),
		max(childSize.y + padding.top + padding.bottom, buttonSize.y),
	};
}

void Button::setColor(color_t new_color) {
	color = new_color;
	redrawSelf = true;
}

void Button::setBorderRadius(radius_t new_radius) {
	borderRadius = new_radius;
	redrawParent = true;
}

} // namespace ui
