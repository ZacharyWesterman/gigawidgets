/// @file polygon.hpp
#pragma once

#include "../shape.hpp"
#include <initializer_list>
#include <vector>

namespace ui {

/**
 * @brief A basic 2D polygon.
 */
struct Polygon : public Shape {
	color_t color;
	std::vector<Coords> points;

	Polygon(color_t color, const std::initializer_list<Coords> &&points);

	void renderAt(const Coords &coords, const shader_t &shader) const override;

	Size getSize() const override;
};

} // namespace ui
