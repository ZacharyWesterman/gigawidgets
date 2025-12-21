/// @file box.hpp
#pragma once

#include "single_child_widget.hpp"

namespace ui {

/**
 * @brief Display a single widget within arbitrary bounds.
 *
 * Normally, the parent widget will specify the bounds as a way to organize multiple widgets on the screen.
 */
class Box : public SingleChildWidget {
	Bounds widgetBounds;

public:
	/**
	 * @brief Construct a Box from a child and Bounds to restrict the child to.
	 * @param child The child widget.
	 * @param bounds The bounds for the child.
	 */
	Box(Widget *child, const Bounds &bounds);

	Bounds bounds() const override;

	/**
	 * @brief Set the bounds for the child widget.
	 * @param bounds The new bounds.
	 */
	void setBounds(const Bounds &bounds);

	void draw() const override;
};

} // namespace ui
