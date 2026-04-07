/// @file spiral.hpp
#pragma once

#include "../shape.hpp"

namespace ui {

/**
 * @brief A spiral shape.
 */
class Spiral : public Shape {
	color_t color;
	float scale;
	float innerRadius;
	float angleTotal;
	float angleStep;
	Size size;

public:
	/**
	 * @brief Construct the spiral.
	 * @param color The spiral color.
	 * @param scale A multiplier that controls the distance between segments after each rotation.
	 * @param innerRadius The distance from the center at which the spiral starts.
	 * @param angleTotal The number of radians that the spiral rotates around the center.
	 * @param angleStep The step size. Larger step sizes are faster to render, but make the curve less round and more angular.
	 */
	Spiral(color_t color, float scale, coord_t innerRadius, float angleTotal, float angleStep = 0.2);

	void renderAt(const Coords &coords, const shader_t &shader) const override;

	Size getSize() const override;
};

} // namespace ui
