/// @file negative.hpp
#pragma once

#include "../core/color.hpp"
#include "../core/coords.hpp"
#include "../core/size.hpp"

namespace ui {
namespace shader {

/**
 * @brief A pixel shader that inverts the colors of an image.
 * @param pixel The original pixel color.
 * @param coords The coords of the current pixel.
 * @param size The total size of the image.
 */
color_t negative(color_t pixel, const Coords &coords, const Size &size) {
	return ~pixel;
}

} // namespace shader
} // namespace ui
