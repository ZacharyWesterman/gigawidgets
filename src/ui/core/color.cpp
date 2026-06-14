#include "color.hpp"

namespace ui {

color_t hsv(const int hue, const float saturation, const float value) {
	const int h = hue % 360;
	const float c = value * saturation;
	const float x = c * (1.f - std::abs(std::fmod(h / 60.f, 2.f) - 1.f));
	const float m = value - c;

	const float r_prime = (h < 60 || h >= 300) ? c : ((h < 120 || h >= 240) ? x : 0.f);
	const float g_prime = (h >= 240) ? 0.f : ((h < 60 || h >= 180) ? x : c);
	const float b_prime = (h < 120) ? 0.f : ((h < 180 || h >= 300) ? x : c);

	const float r = (r_prime + m) * 255.f;
	const float g = (g_prime + m) * 255.f;
	const float b = (b_prime + m) * 255.f;

	return rgb(r, g, b);
}

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
