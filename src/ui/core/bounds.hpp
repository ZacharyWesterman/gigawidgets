#pragma once

#include "coords.hpp"

namespace ui {

struct Bounds {
	Coords min;
	Coords max;

	bool contains(const Coords &point);
};

} // namespace ui
