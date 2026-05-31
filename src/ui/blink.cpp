#include <Arduino.h>

#include "blink.hpp"

namespace ui {

Blink::Blink(Widget *const child, time_t time) : lastRender(0), visible(false), delay(time / 2), SingleChildWidget(child) {}

void Blink::draw() const {
	// Nothing specific to draw here, but in render() will decide whether to draw the child.
}

bool Blink::update(time_t time_ms) {
	const bool updated = SingleChildWidget::update(time_ms);
	if (child->needsRedraw()) {
		redrawSelf = true;
		if (parent) {
			parent->requestRedraw();
		}
	}

	if (time_ms - lastRender >= delay) {
		lastRender = time_ms;
		visible = !visible;
		if (!visible) {
			if (parent) {
				parent->requestRedraw(); // force-redraw the parent if the child was visible but is now hidden.
			}
		}
		return true;
	}

	return updated;
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
