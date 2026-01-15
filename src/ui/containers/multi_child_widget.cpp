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

bool MultiChildWidget::handleEvent(Event &event) {
	if (Widget::handleEvent(event)) {
		const auto b = bounds();

		float inv_width = 1.f / (float)(b.max.x - b.min.x);
		float inv_height = 1.f / (float)(b.max.y - b.min.y);

		for (auto child : children) {
			if (child) {
				for (int i = 0; i < event.contacts; i++) {
					event.coords[i] = {
						(event.points[i].x - b.min.x) * inv_width,
						(event.points[i].y - b.min.y) * inv_height,
					};
				}
				child->handleEvent(event);
			}
		}
		return true;
	}
	return false;
}

bool MultiChildWidget::update(time_t time_ms) {
	for (auto child : children) {
		if (child) {
			if (child->update(time_ms) || child->redrawRequested() || rotationChanged()) {
				redrawParent = true;
			}
		}
	}

	return redrawSelf || redrawParent;
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

Widget *MultiChildWidget::getWidgetById(id_t id) noexcept {
	if (this->id == id) {
		return this;
	}

	for (auto child : children) {
		if (child && child->id == id) {
			return child;
		}
	}
	return nullptr;
}

} // namespace ui
