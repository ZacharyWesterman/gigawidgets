#include "define.h"

Color rgb(uint16_t color565) {
	uint8_t r = color565 >> 8;
	uint8_t g = color565 >> 3 & 0xff;
	uint8_t b = color565 << 3 & 0xff;
	return {r, g, b, 255};
}
