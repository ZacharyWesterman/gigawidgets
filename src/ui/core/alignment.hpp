#pragma once

#include <cinttypes>

namespace ui {

enum align_t {
	ALIGN_CENTER,
	ALIGN_LEFT = 1,
	ALIGN_RIGHT = 2,
	ALIGN_TOP = 1,
	ALIGN_BOTTOM = 2,
};

struct Alignment {
	align_t h;
	align_t v;
};

} // namespace ui
