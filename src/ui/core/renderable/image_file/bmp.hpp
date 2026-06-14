/// @file bmp.hpp
#pragma once

// Comment this out to disable BMP support.
// This should never be needed since BMP support doesn't depend
// on any libraries due to how trivial it is to decode.
#define IMAGE_SUPPORT_BMP

#include "../image_file.hpp"

#ifdef IMAGE_SUPPORT_BMP

namespace ui {

/**
 * @brief A renderable for BMP encoded image data.
 */
struct Bmp : public ImageFile {
	using ImageFile::ImageFile;

	void renderAt(const Coords &coords, const shader_t &shader = 0) const override;
	Size getSize() const override;
};

} // namespace ui

#endif
