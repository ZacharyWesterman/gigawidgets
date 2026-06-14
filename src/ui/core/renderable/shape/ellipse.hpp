/// @file ellipse.hpp
#pragma once

#include "../../radius.hpp"
#include "../shape.hpp"

namespace ui {

/**
 * @brief An ellipse.
 */
struct Ellipse : public Shape {
	/// @brief Whether the shape is filled or just an outline.
	bool fill;
	/// @brief The color of the ellipse.
	color_t color;
	/// @brief The first radius of the ellipse.
	radius_t radius1;
	/// @brief The second radius of the ellipse.
	radius_t radius2;

	/**
	 * @brief Construct an ellipse.
	 * @param color The ellipse color.
	 * @param radius1 The horizontal radius.
	 * @param radius2 The vertical radius.
	 * @param fill Whether to fill the ellipse or just draw an outline.
	 */
	Ellipse(color_t color, radius_t radius1, radius_t radius2, bool fill = false);

	void renderAt(const Coords &coords, const shader_t &shader) const override;

	Size getSize() const override;
};

} // namespace ui
