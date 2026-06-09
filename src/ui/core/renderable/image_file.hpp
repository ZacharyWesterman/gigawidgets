/// @file jpeg.hpp
#pragma once

#include "../renderable.hpp"
#include <initializer_list>

namespace ui {

enum ImageType {
	IMAGE_UNKNOWN,
	IMAGE_JPEG,
	IMAGE_PNG,
	IMAGE_BMP,
};

struct ImageFile : public Renderable {
	static ImageType getType(uint8_t *const bytes, size_t length);
	static bool hasSequence(uint8_t *const bytes, size_t length, const std::initializer_list<uint8_t> &&sequence, size_t index);

	uint8_t *const bytes;
	size_t length;

	ImageFile(uint8_t *const bytes, size_t length);

protected:
	unsigned int getInt(size_t index, uint8_t count) const;
	unsigned int getIntLE(size_t index, uint8_t count) const;
};

} // namespace ui
