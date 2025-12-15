/// @file box.hpp
#pragma once

#include "single_child_widget.hpp"

namespace ui {

class Box : public SingleChildWidget {
	Bounds widgetBounds;

public:
	Box(Widget *child, const Bounds &bounds);

	Bounds bounds() const override;

	void setBounds(const Bounds &bounds);

	void draw() const override;
};

} // namespace ui
