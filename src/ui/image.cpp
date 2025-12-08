#include "image.hpp"

#include <Arduino.h>

namespace ui {

Image::Image(const Renderable *const renderable, const Position &pos, const Alignment &align) : renderable(renderable), Element(pos, align) {}

void Image::draw() const {
	const auto b = bounds();
	renderable->renderAt(b.min, shader);
}

Size Image::size() const {
	return renderable->getSize();
}

void Image::setShader(const std::function<color_t(color_t)> &shader) {
	this->shader = shader;
	redrawSelf = true;
}

void Image::removeShader() {
	this->shader = {};
	redrawSelf = true;
}

} // namespace ui
