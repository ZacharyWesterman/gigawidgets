#pragma once

#include "containers/single_child_element.hpp"
#include "core/color.hpp"
#include "core/radius.hpp"
#include "core/size.hpp"
#include "text.hpp"

namespace ui {

class Button : public SingleChildElement {
	color_t color;
	Size buttonSize;
	radius_t borderRadius;

public:
	Button(Widget *child, color_t color, const Size &size = {0}, radius_t borderRadius = 0, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	void draw() const override;
	bool update(time_t time_ms) override;
	void drawDone() override;

	Size size() const override;

	void setColor(color_t new_color);
	void setBorderRadius(radius_t new_radius);
};

} // namespace ui
