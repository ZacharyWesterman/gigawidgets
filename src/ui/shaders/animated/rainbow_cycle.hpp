/// @file rainbow_cycle.hpp
#pragma once

#include "../../core/color.hpp"
#include "../../core/coords.hpp"
#include "../../core/size.hpp"

namespace ui::shader {

/**
 * @brief A pixel shader that smoothly rotates the original color's hue through the rainbow.
 * @tparam frequency The number of milliseconds it takes to make one full cycle.
 * @param pixel The original pixel color.
 * @param coords The coords of the current pixel.
 * @param size The total size of the image.
 * @param time The current clock time in milliseconds.
 */
template <unsigned int frequency>
color_t rainbow_cycle(color_t pixel, const Coords &coords, const Size &size, time_t time) {
	int h;
	float s, v;
	hsvComponents(pixel, h, s, v);

	h += time * 360 / frequency;

	return hsv(h, s, v);
}

} // namespace ui::shader
