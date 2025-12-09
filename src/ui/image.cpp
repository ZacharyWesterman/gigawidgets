#include "image.hpp"

#include <Arduino.h>

namespace ui {

Image::Image(const Renderable *const renderable, const Position &pos, const Alignment &align) : renderable(renderable), renderEveryFrame(false), Widget(pos, align) {}

void Image::draw() const {
	const auto b = bounds();
	renderable->renderAt(b.min, shader);
}

Size Image::size() const {
	return renderable->getSize();
}

bool Image::update(time_t time_ms) {
	if (renderEveryFrame) {
		return true;
	}
	return Widget::update(time_ms);
}

void Image::setShader(const shader_animated_t &shader) {
	this->shader = shader;
	redrawSelf = true;
	renderEveryFrame = true;
}

void Image::setShader(const shader_oneframe_t &shader) {
	this->shader = [shader](color_t color, const Coords &coords, const Size &size, time_t time_ms) { return shader(color, coords, size); };
	redrawSelf = true;
	renderEveryFrame = false;
}

void Image::removeShader() {
	this->shader = {};
	redrawSelf = true;
	renderEveryFrame = false;
}

} // namespace ui
