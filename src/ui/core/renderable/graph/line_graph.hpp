/// @file line_graph.hpp
#pragma once

#include "../graph.hpp"
#include <vector>

namespace ui {

/// @brief A storage struct representing a point on a graph.
struct GraphPoint {
	/// @brief The horizontal component.
	float x;
	/// @brief The vertical component.
	float y;
};

/// @brief A list of points, representing a line.
typedef std::vector<GraphPoint> GraphLine;

/// @brief A renderable for graphing one or more lines.
struct LineGraph : public Graph {
	/// @brief A list of lines to render.
	std::vector<GraphLine> lines;

	using Graph::Graph;

	virtual void renderAt(const Coords &coords, const shader_t &shader = 0) const override;
};

} // namespace ui
