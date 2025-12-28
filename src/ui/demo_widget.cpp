#include "demo_widget.hpp"

namespace ui {

bool DemoWidget::update(time_t time) {
	return false; // did not update. return true if the widget changed at all.
}

void DemoWidget::draw() const {
	// Only called when the handler detects the widget needs a re-render.

	auto b = parentBounds();

	ui::drawPixel(b.min.x, b.min.y, ui::COLOR_RED);
}

Size DemoWidget::size() const {
	return {0, 0}; // The minimum size of this widget
}

} // namespace ui
