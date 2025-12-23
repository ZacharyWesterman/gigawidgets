#include "column.hpp"
#include "containers/box.hpp"
#include <Arduino.h>

namespace ui {

void Column::calcChildBounds(int index) {
	// We know this Column will ONLY contain ui::Box widgets.
	// Recalc this child based on previous child's bounds.

	auto b = bounds();
	Box *prevChild = index ? reinterpret_cast<Box *>(children[index - 1]) : nullptr;

	uisize_t y = b.min.y;

	if (index) {
		if (childAlignment == ALIGN_TOP) {
			y = prevChild->bounds().max.y + padding.bottom;
		} else {
			y = prevChild->bounds().min.y - padding.top;
			y = b.max.y - y + b.min.y;
		}
	}

	uisize_t minHeight = minimumHeight ? minimumHeight - padding.top - padding.bottom : 0;
	uisize_t height = std::max(minHeight, children[index]->size().y);

	auto ybegin = y + padding.top;
	auto yend = y + padding.top + height;

	if (childAlignment != ALIGN_TOP) {
		ybegin = b.max.y - (ybegin - b.min.y);
		yend = b.max.y - (yend - b.min.y);
		std::swap(ybegin, yend);
	}

	Bounds childBounds = {
		{b.min.x + padding.left, ybegin},
		{b.max.x - padding.right, yend},
	};

	auto child = reinterpret_cast<Box *>(children[index]);
	child->setBounds(childBounds);
}

bool Column::update(time_t time) {
	bool updated = MultiChildWidget::update(time);
	// Don't recalculate bounds if not needed.
	if (!updated) {
		return false;
	}

	// If any of the children need updating, recalculate the bounds for all of them.
	for (size_t i = 0; i < children.size(); i++) {
		calcChildBounds(i);
	}

	return true;
}

void Column::push(Widget *const child) {
	MultiChildWidget::push(new Box(child, {{0, 0}, {0, 0}}));
	calcChildBounds(children.size() - 1);
}

void Column::setMinHeight(uisize_t minHeight) {
	minimumHeight = minHeight;
	redrawSelf = true;
	redrawParent = true;
}

void Column::setChildAlign(align_t align) {
	childAlignment = align;
	redrawSelf = true;
	redrawParent = true;
}

} // namespace ui
