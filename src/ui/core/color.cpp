#include "color.hpp"

namespace ui {

void colorComponents(color_t color, float &red, float &green, float &blue) {
	red = (float)(color >> 8) / 255.f;
	green = (float)(color >> 3 & 0xff) / 255.f;
	blue = (float)(color << 3 & 0xff) / 255.f;
}

float blendComponents(float a, float b, float ratio) {
	return sqrt((1.f - ratio) * a * a + ratio * b * b);
}

color_t blend(color_t color1, color_t color2, float ratio) {
	float r1, g1, b1, r2, g2, b2;
	colorComponents(color1, r1, g1, b1);
	colorComponents(color2, r2, g2, b2);
	return color(blendComponents(r1, r2, ratio), blendComponents(g1, g2, ratio), blendComponents(b1, b2, ratio));
}

} // namespace ui
