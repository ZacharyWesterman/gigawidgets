/// @file bitmap.hpp
#pragma once

#include "../renderable.hpp"

namespace ui {

/**
 * @brief A basic image that is a single color when not transparent.
 */
struct TransparencyMap : public Renderable {
	/// @brief The size of the image in pixels.
	Size size;

	/// @brief The color of non-transparent pixels.
	color_t color;

	/**
	 * @brief The transparency mask.
	 *
	 * Each bit represents its respective pixel's transparency, with 1 being fully opaque and 0 being fully transparent.
	 */
	uint8_t *const mask;

	/**
	 * @brief Construct a transparency map image from static data.
	 * @param size The size of the image.
	 * @param color The color of non-transparent pixels.
	 * @param mask The transparency mask for the image.
	 */
	TransparencyMap(const Size &size, color_t color, uint8_t *const mask);

	/**
	 * @brief Get the size of the transparency map.
	 * @return The size of the transparency map in pixels.
	 */
	Size getSize() const override;

	/**
	 * @brief Display the image directly onto the screen.
	 * @param coords The coordinages to render the first pixel [0,0] of the transparency map.
	 * @param shader An optional pixel shader to apply to each pixel of the transparency map.
	 * @note Shaders will only be applied to \b non-transparent pixels.
	 */
	void renderAt(const Coords &coords, const shader_t &shader = 0) const override;
};

} // namespace ui
