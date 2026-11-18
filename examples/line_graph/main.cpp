#include "src/ui/renderables.hpp"

ui::LineGraph graph;

ui::Renderable &load_graph() {
	graph.viewport = {100_vw, 100_vh};
	graph.lines.push_back({});

	for (int i = 0; i < 10; i++) {
		float x = i;
		float y = random() % 20;
		graph.lines[0].push_back({x, y});
	}

	return graph;
}
