/// @file png.hpp
#pragma once

// Comment this out to disable PNG support.
#define IMAGE_SUPPORT_PNG

#include "../image_file.hpp"

#ifdef IMAGE_SUPPORT_PNG

namespace ui {

struct Png : public ImageFile {
	uint8_t transparencyThreshold = 128;

	using ImageFile::ImageFile;

	void renderAt(const Coords &coords, const shader_t &shader = 0) const override;
	Size getSize() const override;
};

} // namespace ui

#endif
