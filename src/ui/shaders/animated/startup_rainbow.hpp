/// @file startup_rainbow.hpp
#pragma once

#include <time.h>

#include "../../core/color.hpp"
#include "../../core/coords.hpp"
#include "../../core/size.hpp"

namespace ui {
namespace shader {

/**
 * @brief A pixel shader that that animates a rainbow transition from black to white.
 *
 * This is only meant to be used once at startup.
 *
 * @param pixel The original pixel color.
 * @param coords The coords of the current pixel.
 * @param size The total size of the image.
 * @param time The current clock time in milliseconds.
 */
color_t startupRainbow(color_t pixel, const Coords &coords, const Size &size, time_t time);

} // namespace shader
} // namespace ui
