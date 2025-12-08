#pragma once

#include <functional>

#include "coords.hpp"
#include "size.hpp"

namespace ui {

typedef std::function<color_t(color_t, const Coords &, const Size &, time_t)> shader_function_t;

struct Renderable {
	virtual void renderAt(const Coords &coords, const shader_function_t &shader = 0) const = 0;
	virtual Size getSize() const = 0;
};

}; // namespace ui
