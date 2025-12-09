#pragma once

#include "containers/single_child_widget.hpp"
#include "core/color.hpp"

namespace ui {

class Body : public SingleChildWidget {
	color_t backgroundColor;

public:
	Body(Widget *child, color_t backgroundColor = COLOR_BLACK, const Padding &padding = {0});

	void draw() const override;

	Size size() const override;
	Bounds bounds() const override;

	void setColor(color_t new_color);
};

} // namespace ui
