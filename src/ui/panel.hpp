/// @file panel.hpp
#pragma once

#include "containers/single_child_widget.hpp"
#include "core/color.hpp"
#include "core/radius.hpp"
#include "core/size.hpp"

namespace ui {

/**
 * @brief A basic widget that displays a rounded rectangle behind another widget.
 *
 * The child widget is usually some text label, but it can be any arbitrary widget.
 *
 * @note This widget does not automatically update its color etc. when clicked. That is up to the user to implement.
 */
class Panel : public SingleChildWidget {
	color_t color;
	Size panelSize;
	radius_t borderRadius;

public:
	/**
	 * @brief Construct a panel with optional configuration.
	 * @param child The child widget.
	 * @param color The color of the panel.
	 * @param size The minimum size of the panel. It may expand to fit the child widget.
	 * @param borderRadius The radius of the rounded parts of the panel.
	 * @param pos The position of the panel relative to its parent.
	 * @param align The alignment of the panel relative to its parent.
	 * @param padding The padding to apply to the child widget.
	 */
	Panel(Widget *child, color_t color, const Size &size = {0}, radius_t borderRadius = 0, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	void draw() const override;
	bool update(time_t time_ms) override;
	void drawDone() override;
	Size size() const override;

	/**
	 * @brief Set the panel color.
	 * @param new_color The new panel color.
	 */
	void setColor(color_t new_color);

	/**
	 * @brief Set the border radius.
	 * @param new_radius The new radius for the rounded parts of the panel.
	 */
	void setBorderRadius(radius_t new_radius);

	DERIVE_EVENT_HANDLERS(Panel)
};

} // namespace ui
