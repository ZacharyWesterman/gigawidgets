#pragma once

#include "core/element.hpp"
#include "core/renderable.hpp"

namespace ui {

class Image : public Element {
	const Renderable *const renderable;
	shader_t shader;
	bool renderEveryFrame;

public:
	Image(const Renderable *const renderable, const Position &pos, const Alignment &align);

	void draw() const override;
	Size size() const override;
	bool update(time_t time_ms) override;

	void setShader(const shader_animated_t &shader);
	void setShader(const shader_oneframe_t &shader);
	void removeShader();
};

} // namespace ui
