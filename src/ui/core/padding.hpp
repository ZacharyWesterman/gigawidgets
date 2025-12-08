#pragma once

#include <cinttypes>

#include "size.hpp"

namespace ui {

struct Padding {
	uisize_t left;
	uisize_t top;
	uisize_t right;
	uisize_t bottom;

	Padding(uisize_t size);
	Padding(uisize_t left_right, uisize_t top_bottom);
	Padding(uisize_t left, uisize_t top, uisize_t right, uisize_t bottom);
};

} // namespace ui

#define GIGA_DISPLAY_W_PX 480
#define GIGA_DISPLAY_H_PX 800
#define GIGA_DISPLAY_PPI 235.000580145

constexpr int16_t operator"" _px(long double pixels) {
	return pixels;
}

constexpr int16_t operator"" _mm(long double millimeters) {
	return millimeters * GIGA_DISPLAY_PPI / 254;
}

constexpr int16_t operator"" _cm(long double centimeters) {
	return centimeters * GIGA_DISPLAY_PPI / 2.54;
}

constexpr int16_t operator"" _in(long double inches) {
	return inches * GIGA_DISPLAY_PPI;
}

constexpr int16_t operator"" _vw(long double view_width_percent) {
	return view_width_percent * GIGA_DISPLAY_W_PX / 100;
}

constexpr int16_t operator"" _vh(long double view_height_percent) {
	return view_height_percent * GIGA_DISPLAY_H_PX / 100;
}
