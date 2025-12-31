#include "multi_child_widget.hpp"
#include "../core/display.hpp"

namespace ui {

MultiChildWidget::MultiChildWidget(const Position &pos, const Alignment &align, const Padding &padding) : Widget(pos, align, padding) {}

MultiChildWidget::~MultiChildWidget() {
	for (auto child : children) {
		if (child) {
			delete child;
		}
	}
}

void MultiChildWidget::drawDone() {
	Widget::drawDone();
	for (auto child : children) {
		if (child) {
			child->drawDone();
		}
	}
}

void MultiChildWidget::push(Widget *const child) {
	child->setParent(this);
	children.push_back(child);
	redrawSelf = true;
}

bool MultiChildWidget::handleEvent(const Event &event) {
	if (Widget::handleEvent(event)) {
		for (auto child : children) {
			if (child) {
				child->handleEvent(event);
			}
		}
		return true;
	}
	return false;
}

bool MultiChildWidget::update(time_t time_ms) {
	bool updated = false;

	for (auto child : children) {
		if (child) {
			if (child->update(time_ms) || child->redrawRequested() || rotationChanged()) {
				updated = true;
			}
		}
	}

	return updated || redrawSelf || redrawParent;
}

void MultiChildWidget::draw() const {
	for (auto child : children) {
		if (child) {
			child->draw();
		}
	}
}

#ifdef DEBUG
void MultiChildWidget::drawBoundingBox(time_t time) const {
	Widget::drawBoundingBox(time);
	for (auto child : children) {
		if (child) {
			child->drawBoundingBox(time + 500);
		}
	}
}
#endif

} // namespace ui
