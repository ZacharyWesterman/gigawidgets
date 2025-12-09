#pragma once

namespace ui {

#define GIGA_DISPLAY_W_PX 480
#define GIGA_DISPLAY_H_PX 800
#define GIGA_DISPLAY_PPI 235.000580145

constexpr uint16_t operator"" _px(long double pixels) {
	return pixels;
}

constexpr uint16_t operator"" _mm(long double millimeters) {
	return millimeters * GIGA_DISPLAY_PPI / 254;
}

constexpr uint16_t operator"" _cm(long double centimeters) {
	return centimeters * GIGA_DISPLAY_PPI / 2.54;
}

constexpr uint16_t operator"" _in(long double inches) {
	return inches * GIGA_DISPLAY_PPI;
}

constexpr uint16_t operator"" _vw(long double view_width_percent) {
	return view_width_percent * GIGA_DISPLAY_W_PX / 100;
}

constexpr uint16_t operator"" _vh(long double view_height_percent) {
	return view_height_percent * GIGA_DISPLAY_H_PX / 100;
}

constexpr uint16_t operator"" _pt(long double points) {
	// 1 point = 1/72 inch
	return points * GIGA_DISPLAY_PPI / 72.f;
}

} // namespace ui
