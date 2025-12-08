#pragma once

#include "../core/color.hpp"
#include "../core/coords.hpp"
#include "../core/size.hpp"

namespace ui {
namespace shader {

color_t negative(color_t pixel, const Coords &coords, const Size &size, time_t time_ms) {
	return 0xffff - pixel;
}

} // namespace shader
} // namespace ui
