#pragma once

#include "../core/color.hpp"

namespace ui {
namespace shader {

color_t negative(color_t pixel) {
	return 0xffff - pixel;
}

} // namespace shader
} // namespace ui
