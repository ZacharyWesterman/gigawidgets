/// @file jpeg.hpp
#pragma once

// Comment this out to disable JPEG support
#define IMAGE_SUPPORT_JPEG

#include "../image_file.hpp"

#ifdef IMAGE_SUPPORT_JPEG

namespace ui {

/**
 * @brief A renderable for JPEG encoded image data.
 */
struct Jpeg : public ImageFile {
	using ImageFile::ImageFile;

	void renderAt(const Coords &coords, const shader_t &shader = 0) const override;
	Size getSize() const override;

private:
	size_t afterMarker(uint8_t marker, size_t startIndex = 0) const;
};

} // namespace ui

#endif
