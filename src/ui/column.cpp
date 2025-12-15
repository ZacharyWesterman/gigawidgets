#include "column.hpp"
#include "containers/box.hpp"

namespace ui {

void Column::addChild(Widget *const child) {
	auto childSize = child->size();
	auto b = bounds();
	Coords start = b.min;
	Coords end = {b.max.x, b.min.y + childSize.y};

	for (const auto c : children) {
		if (c) {
			auto height = c->size().y;
			start.y += height;
			end.y += height;
		}
	}

	children.push_back(new ui::Box(child, {start, end}));
}

} // namespace ui
