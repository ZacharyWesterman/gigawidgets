#include "image_file.hpp"

namespace ui {

bool ImageFile::hasSequence(uint8_t *const bytes, size_t length, const std::initializer_list<uint8_t> &&sequence, size_t index) {
	if (!bytes || (index + sequence.begin() - sequence.end()) >= (long int)length) {
		return false;
	}

	for (uint8_t byte : sequence) {
		if (bytes[index++] != byte) {
			return false;
		}
	}

	return true;
}

ImageType ImageFile::getType(uint8_t *const bytes, size_t length) {
	if (hasSequence(bytes, length, {'B', 'M'}, 0)) {
		return IMAGE_BMP;
	}

	if (hasSequence(bytes, length, {0xff, 0xd8}, 0) && hasSequence(bytes, length, {0xff, 0xd9}, length - 2)) {
		return IMAGE_JPEG;
	}

	if (hasSequence(bytes, length, {0x89, 'P', 'N', 'G', 0x0d, 0x0a, 0x1a, 0x0a}, 0)) {
		return IMAGE_PNG;
	}

	return IMAGE_UNKNOWN;
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

unsigned int ImageFile::getIntLE(size_t index, uint8_t count) const {
	unsigned int value = 0;
	for (uint8_t i = index + count - 1; i >= index; i--) {
		value <<= 8;
		value += bytes[i];
	}

	return value;
}

} // namespace ui
