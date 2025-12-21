#include "collection.hpp"

namespace ui {

Collection::Collection(const Size &size, const Position &pos, const Alignment &align, const Padding &padding) : widgetSize(size), MultiChildWidget(pos, align, padding) {}

Size Collection::size() const {
	return widgetSize;
}

} // namespace ui
