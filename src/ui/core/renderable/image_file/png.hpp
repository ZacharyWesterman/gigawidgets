/// @file png.hpp
#pragma once

// Comment this out to disable PNG support.
#define IMAGE_SUPPORT_PNG

#include "../image_file.hpp"

#ifdef IMAGE_SUPPORT_PNG

namespace ui {

/**
 * @brief A renderable for PNG encoded image data.
 *
 * @warning Interlaced PNGs are **not** supported, and will not render correctly.
 */
struct Png : public ImageFile {
	/**
	 * @brief The minimum alpha value to consider fully opaque.
	 *
	 * Gigawidgets only supports a single bit of transparency, so
	 * any alpha value below this threshold is considered fully
	 * transparent, and any above this threshold is fully opaque.
	 */
	uint8_t transparencyThreshold = 128;

	using ImageFile::ImageFile;

	void renderAt(const Coords &coords, const shader_t &shader = 0) const override;
	Size getSize() const override;

	/**
	 * @brief Check if this PNG image is interlaced.
	 * @return True if this is interlaced, false otherwise.
	 */
	bool isInterlaced() const;
};

} // namespace ui

#endif
