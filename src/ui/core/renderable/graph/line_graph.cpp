#include "line_graph.hpp"
#include "../../display.hpp"
#include <limits>

namespace ui {

static const color_t DEFAULT_COLORS[] = {
	COLOR_RED,		 //
	COLOR_ORANGE,	 //
	COLOR_YELLOW,	 //
	COLOR_GREEN,	 //
	COLOR_CYAN,		 //
	COLOR_BLUE,		 //
	COLOR_PURPLE,	 //
	COLOR_MAGENTA, //
};

void LineGraph::renderAt(const Coords &coords, const shader_t &shader) const {
	// Get max/min width/height
	float max_x = std::numeric_limits<float>::min();
	float max_y = std::numeric_limits<float>::min();
	float min_x = std::numeric_limits<float>::max();
	float min_y = std::numeric_limits<float>::max();
	for (auto &line : lines) {
		for (auto &point : line) {
			max_x = point.x > max_x ? point.x : max_x;
			max_y = point.y > max_y ? point.y : max_y;
			min_x = point.x < min_x ? point.x : min_x;
			min_y = point.y < min_y ? point.y : min_y;
		}
	}

	float x_scale = 0;
	float y_scale = 0;
	if (max_x > min_x) {
		x_scale = viewport.x / (max_x - min_x);
	}
	if (max_y > min_y) {
		y_scale = viewport.y / (max_y - min_y);
	}

	// Render the graph
	time_t now = millis();
	for (size_t l = 0; l < lines.size(); l++) {
		const auto &line = lines[l];
		color_t pixelColor = colors.size() > l ? colors[l] : DEFAULT_COLORS[l % (sizeof(DEFAULT_COLORS) / sizeof(color_t))];
		if (shader) {
			pixelColor = shader(pixelColor, {0, 0}, viewport, now);
		}
		for (size_t i = 1; i < line.size(); i++) {
			float x0 = coords.x + (line[i - 1].x - min_x) * x_scale;
			float y0 = coords.y + viewport.y - (line[i - 1].y - min_y) * y_scale;
			float x1 = coords.x + (line[i].x - min_x) * x_scale;
			float y1 = coords.y + viewport.y - (line[i].y - min_y) * y_scale;

			drawLine(x0, y0, x1, y1, pixelColor);
		}
	}
}

} // namespace ui
