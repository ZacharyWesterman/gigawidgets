/// @file body.hpp
#pragma once

#include "containers/single_child_widget.hpp"
#include "core/color.hpp"

namespace ui {

/**
 * @brief The root widget of a UI.
 *
 * This widget renders a single-color background onto the screen.
 * To avoid odd rendering artifacts, it should always be used as the root widget.
 */
class Body : public SingleChildWidget {
	/// @brief The background color of the body.
	color_t backgroundColor;

public:
	/**
	 * @brief Construct the body with an optional color and padding for the child widget.
	 * @param child The child widget.
	 * @param backgroundColor The color to fill the screen with.
	 * @param padding The padding to apply to the child widget.
	 */
	Body(Widget *child, color_t backgroundColor = COLOR_BLACK, const Padding &padding = {0});

	void draw() const override;
	Size size() const override;
	Bounds bounds() const override;

	/**
	 * @brief Set the background color.
	 * @param new_color The new background color.
	 */
	void setColor(color_t new_color);

	DERIVE_EVENT_HANDLERS(Body)
};

} // namespace ui
