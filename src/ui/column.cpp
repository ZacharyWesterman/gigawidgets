#include "column.hpp"
#include "containers/box.hpp"
#include <Arduino.h>

namespace ui {

void Column::addChild(Widget *const child) {
	auto childSize = child->size();
	auto b = bounds();

	auto y = b.min.y;

	for (const auto prevChild : children) {
		if (prevChild) {
			auto prevChildHeight = prevChild->size().y;
			y += prevChildHeight + padding.top + padding.bottom;
		}
	}

	b.min.x += padding.left;
	b.max.x -= padding.right;

	b.min.y = y + padding.top;
	b.max.y = y + padding.top + childSize.y;

	children.push_back(new ui::Box(child, b));
}

} // namespace ui
