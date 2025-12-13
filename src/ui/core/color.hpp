/// @file color.hpp
#pragma once

#include <cinttypes>
#include <cmath>

namespace ui {

/**
 * @typedef color_t
 * @brief An RGB565 color value. 5 bits red, 6 bits green, 5 bits blue.
 */
typedef uint16_t color_t;

/**
 * @brief Clamp a normalized color component inside 0 and 1, inclusive.
 * @param color The normalized color component, where 0 is fully dark and 1 is fully bright.
 * @return The color component clamped to within 0 and 1.
 */
constexpr float clampColor(const float color) {
	return (0.f > color) ? 0.f : ((1.f < color) ? 1.f : color);
}

/**
 * @brief Convert normalized color components into an RGB565 value.
 * @param red The normalized red component.
 * @param green The normalized green component.
 * @param blue The normalized blue component.
 * @return The equivalent RGB565 color value.
 */
constexpr color_t color(const float red, const float green, const float blue) {
	return (((uint8_t)(clampColor(red) * 0xff) & 0xF8) << 8) | (((uint8_t)(clampColor(green) * 0xff) & 0xFC) << 3) | ((uint8_t)(clampColor(blue) * 0xff) >> 3);
}

/**
 * @brief Split an RGB565 color value into normalized components.
 * @param color The RGB565 color to split.
 * @param red The normalized red component to output.
 * @param green The normalized green component to output.
 * @param blue The normalized blue component to output.
 */
void colorComponents(color_t color, float &red, float &green, float &blue);

/**
 * @brief Blend two colors, preserving apparent brightness.
 * @param color1 The first color.
 * @param color2 The second color.
 * @param ratio The ratio of the second color to blend into the first. E.g. `0.2` will use 20% of the second color and 80% of the first color.
 * @return A color value between the two colors at the given ratio.
 */
color_t blend(color_t color1, color_t color2, float ratio = 0.5f);

/**
 * @brief A preset list of common colors.
 */
enum {
	/// <span class="color white"></span>
	COLOR_WHITE = 0xffff,
	/// <span class="color black"></span>
	COLOR_BLACK = 0x0000,

	// Mid-range colors

	/// <span class="color gray"></span>
	COLOR_GRAY = 0x7bef,
	/// <span class="color red"></span>
	COLOR_RED = 0xe000,
	/// <span class="color orange"></span>
	COLOR_ORANGE = 0xfbe0,
	/// <span class="color yellow"></span>
	COLOR_YELLOW = 0xffe0,
	/// <span class="color green"></span>
	COLOR_GREEN = 0x07e0,
	/// <span class="color cyan"></span>
	COLOR_CYAN = 0x07ff,
	/// <span class="color blue"></span>
	COLOR_BLUE = 0x001f,
	/// <span class="color magenta"></span>
	COLOR_MAGENTA = 0xf81f,

	// Light colors

	/// <span class="color light-gray"></span>
	COLOR_LIGHT_GRAY = 0xd69a,
	/// <span class="color light-red"></span>
	COLOR_LIGHT_RED = 0xe534,
	/// <span class="color light-orange"></span>
	COLOR_LIGHT_ORANGE = 0xfe11,
	/// <span class="color light-yellow"></span>
	COLOR_LIGHT_YELLOW = 0xfff7,
	/// <span class="color light-green"></span>
	COLOR_LIGHT_GREEN = 0xa7f4,
	/// <span class="color light-cyan"></span>
	COLOR_LIGHT_CYAN = 0xa7ff,
	/// <span class="color light-blue"></span>
	COLOR_LIGHT_BLUE = 0x853f,
	/// <span class="color pink"></span>
	COLOR_PINK = 0xfd3f,
};

} // namespace ui
