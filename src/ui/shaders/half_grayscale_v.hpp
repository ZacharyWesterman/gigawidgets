/// @file half_grayscale_v.hpp
#pragma once

#include "../core/color.hpp"
#include "../core/coords.hpp"
#include "../core/size.hpp"

namespace ui {
namespace shader {

/**
 * @brief A pixel shader that converts the right half of an image to grayscale.
 * @param pixel The original pixel color.
 * @param coords The coords of the current pixel.
 * @param size The total size of the image.
 */
color_t halfGrayscaleV(color_t pixel, const Coords &coords, const Size &size) {
	if (coords.x <= size.x / 2) {
		return pixel;
	}

	float r, g, b;
	colorComponents(pixel, r, g, b);

	float gray = r * 0.299 + g * 0.587 + b * 0.113;
	return color(gray, gray, gray);
}

} // namespace shader
} // namespace ui
