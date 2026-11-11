#include "graph.hpp"

namespace ui {

Graph::Graph() {}
Graph::Graph(Size viewport) : viewport(viewport) {}

Size Graph::getSize() const {
	return viewport;
}

} // namespace ui
