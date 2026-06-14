/// @file jpeg.hpp
#pragma once

#include "../renderable.hpp"
#include <initializer_list>

namespace ui {

/// Supported image file data encodings.
enum ImageType {
	IMAGE_UNKNOWN,
	IMAGE_JPEG,
	IMAGE_PNG,
	IMAGE_BMP,
};

/**
 * @brief The common interface for images read from raw data.
 *
 * @note This is different from the various bitmap renderables as,
 * unlike the bespoke bitmap formats, these image types may be loaded directly from files.
 */
struct ImageFile : public Renderable {

	/**
	 * @brief Determine the image type based on the file data.
	 * @param bytes A buffer containing the image data.
	 * @param length The size of the buffer.
	 * @return The type of image that was determined, or `IMAGE_UNKNOWN` (aka `0`) if unable to be determined.
	 */
	static ImageType getType(uint8_t *const bytes, size_t length);

	/**
	 * @brief Check if a buffer contains a specific sequence of bytes at the given index.
	 * @param bytes A buffer containing the image data.
	 * @param length The size of the buffer.
	 * @param sequence A sequence of bytes.
	 * @param index The index to look at.
	 */
	static bool hasSequence(uint8_t *const bytes, size_t length, const std::initializer_list<uint8_t> &&sequence, size_t index);

	/**
	 * @brief The buffer that the image data is stored in.
	 *
	 * @note This buffer is NOT owned by the ImageFile instance, and will not be cleaned up by it.
	 * Any cleanup/deletion must be done be the caller or owning entity.
	 */
	uint8_t *const bytes;

	/**
	 * @brief The size of the data buffer.
	 */
	size_t length;

	/**
	 * @brief Constructor.
	 * @param bytes A buffer containing the image data.
	 * @param length The size of the buffer.
	 */
	ImageFile(uint8_t *const bytes, size_t length);

protected:
	/**
	 * @brief Read a big-endian integer from raw bytes.
	 * @param index The starting index.
	 * @param count The number of bytes to read.
	 * @return The resulting integer.
	 */
	unsigned int getInt(size_t index, uint8_t count) const;

	/**
	 * @brief Read a little-endian integer from raw bytes.
	 * @param index The starting index.
	 * @param count The number of bytes to read.
	 * @return The resulting integer.
	 */
	unsigned int getIntLE(size_t index, uint8_t count) const;
};

} // namespace ui
