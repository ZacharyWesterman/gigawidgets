#include "startup_rainbow.hpp"

namespace ui {
namespace shader {

color_t startupRainbow(color_t pixel, const Coords &coords, const Size &size, time_t time) {
	time = (time - 3000) * 3 / 2;

	if (coords.x < time) {
		return ui::COLOR_WHITE;
	} else if (coords.x - 100 < time) {
		return ui::COLOR_PINK;
	} else if (coords.x - 200 < time) {
		return ui::COLOR_MAGENTA;
	} else if (coords.x - 300 < time) {
		return ui::COLOR_PURPLE;
	} else if (coords.x - 400 < time) {
		return ui::COLOR_BLUE;
	} else if (coords.x - 500 < time) {
		return ui::COLOR_CYAN;
	} else if (coords.x - 600 < time) {
		return ui::COLOR_GREEN;
	} else if (coords.x - 700 < time) {
		return ui::COLOR_YELLOW;
	} else if (coords.x - 800 < time) {
		return ui::COLOR_ORANGE;
	} else if (coords.x - 900 < time) {
		return ui::COLOR_RED;
	}

	return ui::COLOR_BLACK;
}

} // namespace shader
} // namespace ui
