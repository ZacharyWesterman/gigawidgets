/// @file bitmap.hpp
#pragma once

#include "../renderable.hpp"

namespace ui {

/**
 * @brief A basic image with no compression or transparency.
 */
struct Bitmap : public Renderable {
	/// @brief The size of the image in pixels.
	Size size;
	/// @brief The list of pixels in the image.
	color_t *const data;

	/**
	 * @brief Construct a bitmap image from static data.
	 * @param size The size of the image.
	 * @param data The list of pixels in the image.
	 */
	Bitmap(const Size &size, color_t *const data);

	/**
	 * @brief Display the bitmap directly onto the screen.
	 * @param coords The coordinates to render the first pixel [0,0] of the bitmap.
	 * @param shader An optional pixel shader to apply to each pixel of the bitmap.
	 */
	void renderAt(const Coords &coords, const shader_t &shader = 0) const override;

	/**
	 * @brief Get the size of the bitmap.
	 * @return The size of the bitmap in pixels.
	 */
	Size getSize() const override;

	/**
	 * @brief Get the average color of the bitmap.
	 * @return A calculated average of the color from all pixels in the bitmap.
	 * @note This performs a fast, naive average (mean) of the raw pixel data, without accounting for human perception.
	 */
	virtual color_t averageColor() const;
};

} // namespace ui
