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

Widget *SingleChildWidget::getChild() const {
	return child;
}

bool SingleChildWidget::handleEvent(Event &event) {
	if (Widget::handleEvent(event)) {
		auto b = bounds();

		float inv_width = 1.f / (float)(b.max.x - b.min.x);
		float inv_height = 1.f / (float)(b.max.y - b.min.y);

		for (int i = 0; i < event.contacts; i++) {
			event.coords[i] = {
				(event.points[i].x - b.min.x) * inv_width,
				(event.points[i].y - b.min.y) * inv_height,
			};
		}

		child->handleEvent(event);
		return true;
	}
	return false;
}

bool SingleChildWidget::update(time_t time_ms) {
	auto updated = child->update(time_ms);
	redrawSelf |= child->redrawRequested();
	return updated || redrawSelf || rotationChanged();
}

#ifdef DEBUG
void SingleChildWidget::drawBoundingBox(time_t time) const {
	Widget::drawBoundingBox(time);
	child->drawBoundingBox(time + 500);
}
#endif

Widget *SingleChildWidget::getWidgetById(id_t id) noexcept {
	if (this->id == id) {
		return this;
	}
	return child ? child->getWidgetById(id) : nullptr;
}

} // namespace ui
