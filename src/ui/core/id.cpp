#include "id.hpp"

namespace ui {

id_t id(const char *str, int size) noexcept {
	id_t crc = 0xFFFFFFFF;
	for (int i = 0; i < size; ++i) {
		crc = (crc >> 8) ^ hash32::crc_table[(crc ^ str[i]) & 0xFF];
	}
	return crc ^ 0xFFFFFFFF;
}

} // namespace ui
