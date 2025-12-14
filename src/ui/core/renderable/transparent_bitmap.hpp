/// @file bitmap.hpp
#pragma once

#include "bitmap.hpp"

namespace ui {

/**
 * @brief A basic image with no compression, and with 1 bit of transparency per pixel.
 */
struct TransparentBitmap : public Bitmap {
	/**
	 * @brief The transparency mask.
	 *
	 * Each bit represents its respective pixel's transparency, with 1 being fully opaque and 0 being fully transparent.
	 */
	uint8_t *const mask;

	/**
	 * @brief Construct a transparent bitmap image from static data.
	 * @param size The size of the image.
	 * @param data The list of pixels in the image.
	 * @param mask The transparency mask for the image.
	 */
	TransparentBitmap(const Size &size, color_t *const data, uint8_t *const mask);

	/**
	 * @brief Display the bitmap directly onto the screen.
	 * @param coords The coordinages to render the first pixel [0,0] of the bitmap.
	 * @param shader An optional pixel shader to apply to each pixel of the bitmap.
	 * @note Shaders will only be applied to \b non-transparent pixels.
	 */
	void renderAt(const Coords &coords, const shader_t &shader = 0) const override;

	/**
	 * @brief Get the average color of the bitmap.
	 * @return A calculated average of the color from all pixels in the bitmap, excluding transparent pixels.
	 * @note This performs a fast, naive average (mean) of the raw pixel data, without accounting for human perception.
	 */
	color_t averageColor() const override;
};

} // namespace ui
