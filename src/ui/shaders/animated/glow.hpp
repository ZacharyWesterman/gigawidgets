/// @file glow.hpp
#pragma once

#include "../../core/color.hpp"
#include "../../core/coords.hpp"
#include "../../core/size.hpp"

namespace ui {
namespace shader {

template <unsigned int frequency>
color_t glow(color_t pixel, const Coords &coords, const Size &size, time_t time_ms) {
	float r, g, b;
	colorComponents(pixel, r, g, b);

	float ratio = .5f - sin(time_ms * (6.283f / (float)frequency)) / 2.f;

	return blend(pixel, ui::COLOR_WHITE, ratio);
}

} // namespace shader
} // namespace ui
