/// @file jpeg.hpp
#pragma once

#include "../renderable.hpp"

namespace ui {

enum class ImageType {
	UNKNOWN,
	JPEG, // Currently only JPEG supported!
};

struct ImageFile : public Renderable {
	static ImageType getType(uint8_t *bytes, size_t length);

	uint8_t *const bytes;
	size_t length;

	ImageFile(uint8_t *const bytes, size_t length);

protected:
	unsigned int getInt(size_t index, uint8_t count) const;
};
} // namespace ui

#include "image_file/jpeg.hpp"
