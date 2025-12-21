/// @file collection.hpp
#pragma once

#include "containers/multi_child_widget.hpp"

namespace ui {

class Collection : public MultiChildWidget {
	Size widgetSize;

public:
	Collection(const Size &size, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	Size size() const override;
};

} // namespace ui
