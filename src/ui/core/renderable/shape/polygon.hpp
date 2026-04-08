/// @file polygon.hpp
#pragma once

#include "../../bounds.hpp"
#include "../shape.hpp"

#include <initializer_list>
#include <vector>

namespace ui {

/**
 * @brief A basic 2D polygon.
 * @note Setting `fill` to true on self-intersecting polygons may yield unexpected results.
 */
struct Polygon : public Shape {
	/// @brief Whether the shape is filled or just an outline.
	bool fill;
	/// @brief The color of the polygon.
	color_t color;
	/// @brief The polygon vertices.
	std::vector<Coords> points;

	/**
	 * @brief Construct polygon from a set list of points.
	 * @param color The polygon color.
	 * @param points A list of points.
	 * @param fill Whether to fill the polygon or just draw an outline.
	 */
	Polygon(color_t color, const std::initializer_list<Coords> &&points, bool fill = false);

	/**
	 * @brief Construct a polygon without any points.
	 * @param color The polygon color.
	 * @param fill Whether to fill the polygon or just draw an outline.
	 */
	Polygon(color_t color, bool fill = false);

	void renderAt(const Coords &coords, const shader_t &shader) const override;

	Size getSize() const override;

private:
	Bounds getBounds() const;
};

} // namespace ui
