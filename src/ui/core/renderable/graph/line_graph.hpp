/// @file line_graph.hpp
#pragma once

#include "../graph.hpp"
#include <vector>

namespace ui {

struct GraphPoint {
	float x;
	float y;
};

typedef std::vector<GraphPoint> GraphLine;

struct LineGraph : public Graph {
	/// @brief A list of lines to render.
	std::vector<GraphLine> lines;

	using Graph::Graph;

	virtual void renderAt(const Coords &coords, const shader_t &shader = 0) const override;
};

} // namespace ui
