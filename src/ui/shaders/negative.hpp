#pragma once

#include "../core/color.hpp"
#include "../core/coords.hpp"
#include "../core/size.hpp"

namespace ui {
namespace shader {

color_t negative(color_t pixel, const Coords &coords, const Size &size) {
	return ~pixel;
}

} // namespace shader
} // namespace ui
