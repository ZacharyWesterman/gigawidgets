#include "single_child_widget.hpp"
#include "../core/display.hpp"

namespace ui {

SingleChildWidget::SingleChildWidget(Widget *const child, const Position &pos, const Alignment &align, const Padding &padding) : child(child), Widget(pos, align, padding) {
	child->setParent(this);
}

SingleChildWidget::~SingleChildWidget() {
	delete child;
}

Size SingleChildWidget::size() const {
	return child->size();
}

void SingleChildWidget::drawDone() {
	Widget::drawDone();
	child->drawDone();
}

void SingleChildWidget::setChild(Widget *const child) {
	delete this->child;
	this->child = child;
	child->setParent(this);
}

bool SingleChildWidget::handleEvent(const Event &event) {
	if (Widget::handleEvent(event)) {
		child->handleEvent(event);
	}
}

bool SingleChildWidget::update(time_t time_ms) {
	return child->update(time_ms) || child->redrawRequested() || rotationChanged();
}

} // namespace ui
