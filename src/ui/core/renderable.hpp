#pragma once

#include <functional>

#include "coords.hpp"
#include "size.hpp"

namespace ui {

struct Renderable {
	virtual void renderAt(const Coords &coords, const std::function<color_t(color_t)> &shader = 0) const = 0;
	virtual Size getSize() const = 0;
};

}; // namespace ui
