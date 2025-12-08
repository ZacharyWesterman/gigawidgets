#pragma once

#include "core/bitmap.hpp"
#include "core/element.hpp"

namespace ui {

class Image : public Element {
	const Renderable *const renderable;
	std::function<color_t(color_t)> shader;

public:
	Image(const Renderable *const renderable, const Position &pos, const Alignment &align);

	void draw() const override;
	Size size() const override;

	void setShader(const std::function<color_t(color_t)> &shader);
	void removeShader();
};

} // namespace ui
