#include "color.hpp"

namespace ui {

void colorComponents(color_t color, float &red, float &green, float &blue) {
	red = (float)(color >> 8) / 255.f;
	green = (float)(color >> 3 & 0xff) / 255.f;
	blue = (float)(color << 3 & 0xff) / 255.f;
}

} // namespace ui
