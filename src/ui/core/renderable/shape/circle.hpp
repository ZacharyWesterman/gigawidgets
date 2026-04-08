/// @file circle.hpp
#pragma once

#include "../../radius.hpp"
#include "../shape.hpp"

namespace ui {

/**
 * @brief A circle.
 */
struct Circle : public Shape {
	/// @brief Whether the shape is filled or just an outline.
	bool fill;
	/// @brief The color of the circle.
	color_t color;
	/// @brief The radius of the circle.
	radius_t radius;

	/**
	 * @brief Construct a circle.
	 * @param color The circle color.
	 * @param radius The circle radius.
	 * @param fill Whether to fill the circle or just draw an outline.
	 */
	Circle(color_t color, radius_t radius, bool fill = false);

	void renderAt(const Coords &coords, const shader_t &shader) const override;

	Size getSize() const override;
};

} // namespace ui
