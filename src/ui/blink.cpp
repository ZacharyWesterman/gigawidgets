#include <Arduino.h>

#include "blink.hpp"

namespace ui {

Blink::Blink(Widget *const child, time_t time) : lastRender(0), visible(false), delay(time / 2), SingleChildWidget(child) {}

void Blink::draw() const {
	// Nothing specific to draw here, but in render() will decide whether to draw the child.
}

void Blink::render(bool force) const {
	if (visible) {
		SingleChildWidget::render(force);
	}
}

void Blink::update(time_t time_ms) {
	SingleChildWidget::update(time_ms);
	if (redrawSelf) {
		requestParentRedraw();
	}

	if (time_ms - lastRender >= delay) {
		lastRender = time_ms;
		visible = !visible;
		requestParentRedraw(); // force-redraw the parent if the child was visible but is now hidden.
	}
}

Size Blink::size() const {
	return child->size();
}

Bounds Blink::bounds() const {
	return parentBounds();
}

void Blink::drawDone() {
	redrawSelf = false;
	child->drawDone();
}

} // namespace ui
