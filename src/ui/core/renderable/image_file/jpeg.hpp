/// @file jpeg.hpp
#pragma once

#include "../image_file.hpp"

namespace ui {

struct Jpeg : public ImageFile {
	using ImageFile::ImageFile;

	void renderAt(const Coords &coords, const shader_t &shader = 0) const override;
	Size getSize() const override;

private:
	size_t afterMarker(uint8_t marker, size_t startIndex = 0) const;
};

} // namespace ui
