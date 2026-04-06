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
	Spiral(color_t color, float scale, coord_t innerRadius, float angleTotal, float angleStep = 0.2);

	void renderAt(const Coords &coords, const shader_t &shader) const override;

	Size getSize() const override;
};

} // namespace ui
