#pragma once

#include <functional>

#include "color.hpp"
#include "coords.hpp"
#include "size.hpp"

namespace ui {

typedef std::function<color_t(color_t, const Coords &, const Size &)> shader_oneframe_t;
typedef std::function<color_t(color_t, const Coords &, const Size &, time_t)> shader_animated_t;
typedef shader_animated_t shader_t;

struct Renderable {
	virtual void renderAt(const Coords &coords, const shader_t &shader = 0) const = 0;
	virtual Size getSize() const = 0;
};

}; // namespace ui
