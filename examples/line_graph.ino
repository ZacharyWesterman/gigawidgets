// Renders an ellipse to the screen that oscillates its radii and cycles through the rainbow.

#include "src/ui.hpp"
#include "src/ui/renderables.hpp"
#include "src/ui/shaders.hpp"

ui::LineGraph graph;
ui::Image *image = nullptr;

void add_point_to_all_lines() {
	for (auto &line : graph.lines) {
		float x = line.size();
		float y = random() % 20;
		line.push_back({x, y});
	}

	// Request that parent Image redraw itself.
	// 1. Have to force a redraw here since the Image doesn't know the shape changed.
	// 2. Have to specify that the PARENT redraws, otherwise will get weird overdraw.
	image->requestParentRedraw();
	ui::setTimeout(add_point_to_all_lines, 500);
}

void setup() {
	// Create basic UI
	ui::setRotation(ui::ROT_90_DEG);

	image = new ui::Image(graph);

	auto panel = new ui::Panel(
		image, //child widget
		ui::color(0.2, 0.2, 0.2), //color
		{0,0}, //minimum size
		5_px, //border radius
		{0,0}, //position
		{ui::ALIGN_LEFT, ui::ALIGN_CENTER}, //alignment in parent
		{5_px} //padding
    );

	auto body = new ui::Body(panel, ui::COLOR_BLACK);
	ui::setRoot(body);

	// Graph has a few lines
	graph.lines = {{}, {}, {}, {}};
    // Set how much space the graph takes up.
	graph.viewport = {100_vw - 10_px, 50_vh - 10_px};
    // You can set your own colors too. If not set, it will use a list of default colors.
    graph.colors = {ui::COLOR_WHITE, ui::COLOR_RED, ui::COLOR_GREEN, ui::COLOR_BLUE};

	// Add line to graph every so often.
	ui::setTimeout(add_point_to_all_lines, 1);
}

void loop() {
	ui::render();
}
