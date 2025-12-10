#pragma once

#include <cinttypes>
#include <cmath>

namespace ui {

typedef uint16_t color_t;

constexpr float clampColor(const float color) {
	return (0.f > color) ? 0.f : ((1.f < color) ? 1.f : color);
}

constexpr color_t color(const float red, const float green, const float blue) {
	return (((uint8_t)(clampColor(red) * 0xff) & 0xF8) << 8) | (((uint8_t)(clampColor(green) * 0xff) & 0xFC) << 3) | ((uint8_t)(clampColor(blue) * 0xff) >> 3);
}

void colorComponents(color_t color, float &red, float &green, float &blue);

color_t blend(color_t color1, color_t color2, float ratio = 0.5f);

enum {
	COLOR_WHITE = 0xffff,
	COLOR_BLACK = 0x0000,

	// Mid-range colors
	COLOR_GRAY = 0x7bef,
	COLOR_RED = 0xe000,
	COLOR_ORANGE = 0xfbe0,
	COLOR_YELLOW = 0xffe0, // 0b11111'111111'00000
	COLOR_GREEN = 0x07e0,
	COLOR_CYAN = 0x07ff,
	COLOR_BLUE = 0x001f,
	COLOR_MAGENTA = 0xf81f,

	// Light colors
	COLOR_LIGHT_GRAY = 0xd69a,
	COLOR_LIGHT_RED = 0xe534,
	COLOR_LIGHT_ORANGE = 0xfe11,
	COLOR_LIGHT_YELLOW = 0xfff7,
	COLOR_LIGHT_GREEN = 0xa7f4,
	COLOR_LIGHT_CYAN = 0xa7ff,
	COLOR_LIGHT_BLUE = 0x853f,
	COLOR_PINK = 0xfd3f,
};

} // namespace ui
