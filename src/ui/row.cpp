#include "row.hpp"
#include "containers/box.hpp"
#include <Arduino.h>

namespace ui {

void Row::calcChildBounds(int index) {
	// We know this Row will ONLY contain ui::Box widgets.
	// Recalc this child based on previous child's bounds.

	auto b = bounds();
	Box *prevChild = index ? reinterpret_cast<Box *>(children[index - 1]) : nullptr;

	uisize_t x = b.min.x;

	if (index) {
		if (childAlignment == ALIGN_LEFT) {
			x = prevChild->bounds().max.x + padding.right;
		} else {
			x = prevChild->bounds().min.x - padding.left;
			x = b.max.x - x + b.min.x;
		}
	}

	uisize_t width = max(minimumWidth - padding.left - padding.right, children[index]->size().x);

	auto xbegin = x + padding.left;
	auto xend = x + padding.left + width;

	if (childAlignment != ALIGN_LEFT) {
		xbegin = b.max.x - (xbegin - b.min.x);
		xend = b.max.x - (xend - b.min.x);
		std::swap(xbegin, xend);
	}

	Bounds childBounds = {
		{xbegin, b.min.y + padding.top},
		{xend, b.max.y - padding.bottom},
	};

	auto child = reinterpret_cast<Box *>(children[index]);
	child->setBounds(childBounds);
}

bool Row::update(time_t time) {
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

void Row::push(Widget *const child) {
	MultiChildWidget::push(new Box(child, {{0, 0}, {0, 0}}));
	calcChildBounds(children.size() - 1);
}

void Row::setMinWidth(uisize_t minWidth) {
	minimumWidth = minWidth;
	redrawSelf = true;
	redrawParent = true;
}

void Row::setChildAlign(align_t align) {
	childAlignment = align;
	redrawSelf = true;
	redrawParent = true;
}

} // namespace ui
