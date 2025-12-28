#include "demo_widget.hpp"
#include "core/color.hpp"
#include "core/display.hpp"

namespace ui {

bool DemoWidget::update(time_t time) {
	return false; // did not update. return true if the widget changed at all.
}

void DemoWidget::draw() const {
	// Only called when the handler detects the widget needs a re-render.

	// auto b = parentBounds();

	// ui::drawLine(200, 200, 300, 300, ui::COLOR_RED);

	ui::drawPolygon(160, 120, 80, 5, ui::COLOR_GREEN, 0.0f);
}

Size DemoWidget::size() const {
	return {0, 0}; // The minimum size of this widget
}

} // namespace ui
