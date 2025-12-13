/// @file glow.hpp
#pragma once

#include "../../core/color.hpp"
#include "../../core/coords.hpp"
#include "../../core/size.hpp"

namespace ui {
namespace shader {

/**
 * @brief A pixel shader that smoothly cycles between an image's original color and white.
 * @tparam frequency The number of milliseconds it takes to make one full cycle.
 * @param pixel The original pixel color.
 * @param coords The coords of the current pixel.
 * @param size The total size of the image.
 * @param time The current clock time in milliseconds.
 */
template <unsigned int frequency>
color_t glow(color_t pixel, const Coords &coords, const Size &size, time_t time) {
	float r, g, b;
	colorComponents(pixel, r, g, b);

	float ratio = .5f - sin(time * (6.283f / (float)frequency)) / 2.f;

	return blend(pixel, ui::COLOR_WHITE, ratio);
}

} // namespace shader
} // namespace ui
