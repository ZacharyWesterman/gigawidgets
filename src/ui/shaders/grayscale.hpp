#pragma once

#include "../core/color.hpp"

namespace ui {
namespace shader {

color_t grayscale(color_t pixel) {
	float r, g, b;
	colorComponents(pixel, r, g, b);

	float gray = r * 0.299 + g * 0.587 + b * 0.113;
	return color(gray, gray, gray);
}

} // namespace shader
} // namespace ui
