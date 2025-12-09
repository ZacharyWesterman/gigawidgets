#pragma once

#include <cinttypes>

#include "size.hpp"

namespace ui {

struct Padding {
	uisize_t left;
	uisize_t top;
	uisize_t right;
	uisize_t bottom;

	Padding(uisize_t size);
	Padding(uisize_t left_right, uisize_t top_bottom);
	Padding(uisize_t left, uisize_t top, uisize_t right, uisize_t bottom);
};

} // namespace ui
