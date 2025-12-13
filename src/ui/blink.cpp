#include <Arduino.h>

#include "blink.hpp"

namespace ui {

Blink::Blink(Widget *const child, time_t time) : lastRender(0), visible(false), delay(time / 2), SingleChildWidget(child) {}

void Blink::draw() const {
	if (visible) {
		child->draw();
	}
}

bool Blink::update(time_t time_ms) {
	const bool updated = SingleChildWidget::update(time_ms);
	redrawParent = child->redrawRequested();

	if (time_ms - lastRender >= delay) {
		lastRender = time_ms;
		visible = !visible;
		if (!visible) {
			redrawParent = true; // force-redraw the parent if the child was visible but is now hidden.
		}
		return true;
	}

	return updated;
}

Size Blink::size() const {
	return child->size();
}

void Blink::drawDone() {
	redrawParent = false;
	child->drawDone();
}

} // namespace ui
