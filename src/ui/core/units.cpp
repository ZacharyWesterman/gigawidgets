#include "units.hpp"
#include "display.hpp"

uint16_t operator""_vw(long double view_width_percent) {
	return view_width_percent * ui::width() / 100;
}

uint16_t operator""_vw(unsigned long long view_width_percent) {
	return view_width_percent * ui::width() / 100;
}

uint16_t operator""_vh(long double view_height_percent) {
	return view_height_percent * ui::height() / 100;
}

uint16_t operator""_vh(unsigned long long view_height_percent) {
	return view_height_percent * ui::height() / 100;
}
