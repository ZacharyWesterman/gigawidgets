/// @file oval.hpp
#pragma once

#include "../../radius.hpp"
#include "../shape.hpp"

namespace ui {

/**
 * @brief An oval.
 */
struct Oval : public Shape {
	/// @brief Whether the shape is filled or just an outline.
	bool fill;
	/// @brief The color of the oval.
	color_t color;
	/// @brief The first radius of the oval.
	radius_t radius1;
	/// @brief The second radius of the oval.
	radius_t radius2;
	/// @brief The angle of the shape.
	float angle;

	/**
	 * @brief Construct a oval.
	 * @param color The oval color.
	 * @param radius1 The oval radius.
	 * @param fill Whether to fill the oval or just draw an outline.
	 */
	Oval(color_t color, radius_t radius1, radius_t radius2, float angle = 0.f, bool fill = false);

	void renderAt(const Coords &coords, const shader_t &shader) const override;

	Size getSize() const override;
};

} // namespace ui
