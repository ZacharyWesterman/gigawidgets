/// @file graph.hpp
#pragma once

#include "../color.hpp"
#include "../renderable.hpp"
#include <vector>

namespace ui {

/**
 * @brief The common interface for rendering graphs and charts.
 */
struct Graph : public Renderable {
	/// @brief The size of the graph viewport.
	Size viewport;
	/// @brief A list of colors to render the graph in.
	std::vector<color_t> colors;

	/// @brief Construct a graph without setting the viewport.
	Graph();

	/**
	 * @brief Construct a graph with a viewport.
	 * @param viewport The size of the graph viewport.
	 */
	Graph(Size viewport);

	virtual Size getSize() const override;
};

} // namespace ui
