/// @file bitmap.hpp
#pragma once

#include "transparency_map.hpp"

namespace ui {

/**
 * @brief A basic image that is a single color when not transparent.
 */
struct CompressedTransparencyMap : public TransparencyMap {
	using TransparencyMap::TransparencyMap;

	/**
	 * @brief Display the image directly onto the screen.
	 * @param coords The coordinages to render the first pixel [0,0] of the transparency map.
	 * @param shader An optional pixel shader to apply to each pixel of the transparency map.
	 * @note Shaders will only be applied to \b non-transparent pixels.
	 */
	void renderAt(const Coords &coords, const shader_t &shader = 0) const override;
};

} // namespace ui
