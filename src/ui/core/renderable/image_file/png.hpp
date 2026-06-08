/// @file png.hpp
#pragma once

#include "../image_file.hpp"

#if defined(__has_include) && __has_include(<PNGdec.h>)
#define IMAGE_SUPPORT_PNG
#endif

#ifdef IMAGE_SUPPORT_PNG

namespace ui {

struct Png : public ImageFile {
	using ImageFile::ImageFile;

	void renderAt(const Coords &coords, const shader_t &shader = 0) const override;
	Size getSize() const override;

private:
	size_t afterMarker(uint8_t marker, size_t startIndex = 0) const;
};

} // namespace ui

#endif
