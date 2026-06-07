#include "image_file.hpp"

namespace ui {

ImageType ImageFile::getType(uint8_t *const bytes, size_t length) {
	if (!bytes) {
		return ImageType::UNKNOWN;
	}

	if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[length - 2] == 0xff && bytes[length - 1] == 0xd9) {
		return ImageType::JPEG;
	}

	return ImageType::UNKNOWN;
}

ImageFile::ImageFile(uint8_t *bytes, size_t length) : bytes(bytes), length(length) {}

unsigned int ImageFile::getInt(size_t index, uint8_t count) const {
	unsigned int value = 0;

	for (uint8_t i = index; i < index + count; i++) {
		value <<= 8;
		value += bytes[i];
	}

	return value;
}

} // namespace ui
