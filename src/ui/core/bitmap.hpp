#pragma once

#include "color.hpp"
#include "coords.hpp"
#include "renderable.hpp"

namespace ui {

struct Bitmap : public Renderable {
	Size size;
	color_t *const data;

	Bitmap(const Size &size, color_t *const data);
	void renderAt(const Coords &coords, const shader_t &shader = 0) const override;
	Size getSize() const override;

	virtual color_t averageColor() const;
};

struct TransparentBitmap : public Bitmap {
	uint8_t *const mask;

	TransparentBitmap(const Size &size, color_t *const data, uint8_t *const mask);
	void renderAt(const Coords &coords, const shader_t &shader = 0) const override;

	color_t averageColor() const override;
};

} // namespace ui
