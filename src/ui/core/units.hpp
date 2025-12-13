/// @file units.hpp
#pragma once

#include <cinttypes>

#define GIGA_DISPLAY_W_PX 480
#define GIGA_DISPLAY_H_PX 800
#define GIGA_DISPLAY_PPI 235.000580145

/**
 * @brief The custom units operator for pixels.
 *
 * This operator is included for consistency,
 * to allow for writing sizes like `25.0_px` instead of just `25`.
 * In reality, no transformation is applied.
 *
 * @param pixels The size in pixels.
 * @return The size in pixels.
 */
constexpr uint16_t operator""_px(long double pixels) {
	return pixels;
}

/**
 * @brief The custom units operator for pixels.
 *
 * This operator is included for consistency,
 * to allow for writing sizes like `25_px` instead of just `25`.
 * In reality, no transformation is applied.
 *
 * @param pixels The size in pixels.
 * @return The size in pixels.
 */
constexpr uint16_t operator""_px(unsigned long long pixels) {
	return pixels;
}

/**
 * @brief The custom units operator for millimeters.
 *
 * This operator allows for writing sizes like `2.5_mm`,
 * which will automatically be converted to pixels at compile time.
 *
 * @param millimeters The size in millimeters.
 * @return The size in pixels.
 */
constexpr uint16_t operator""_mm(long double millimeters) {
	return millimeters * GIGA_DISPLAY_PPI / 254;
}

/**
 * @brief The custom units operator for millimeters.
 *
 * This operator allows for writing sizes like `25_mm`,
 * which will automatically be converted to pixels at compile time.
 *
 * @param millimeters The size in millimeters.
 * @return The size in pixels.
 */
constexpr uint16_t operator""_mm(unsigned long long millimeters) {
	return millimeters * GIGA_DISPLAY_PPI / 254;
}

/**
 * @brief The custom units operator for centimeters.
 *
 * This operator allows for writing sizes like `2.5_cm`,
 * which will automatically be converted to pixels at compile time.
 *
 * @param centimeters The size in centimeters.
 * @return The size in pixels.
 */
constexpr uint16_t operator""_cm(long double centimeters) {
	return centimeters * GIGA_DISPLAY_PPI / 2.54;
}

/**
 * @brief The custom units operator for centimeters.
 *
 * This operator allows for writing sizes like `2_cm`,
 * which will automatically be converted to pixels at compile time.
 *
 * @param centimeters The size in centimeters.
 * @return The size in pixels.
 */
constexpr uint16_t operator""_cm(unsigned long long centimeters) {
	return centimeters * GIGA_DISPLAY_PPI / 2.54;
}

/**
 * @brief The custom units operator for inches.
 *
 * This operator allows for writing sizes like `0.5_in`,
 * which will automatically be converted to pixels at compile time.
 *
 * @param inches The size in inches.
 * @return The size in pixels.
 */
constexpr uint16_t operator""_in(long double inches) {
	return inches * GIGA_DISPLAY_PPI;
}

/**
 * @brief The custom units operator for inches.
 *
 * This operator allows for writing sizes like `1_in`,
 * which will automatically be converted to pixels at compile time.
 *
 * @param inches The size in inches.
 * @return The size in pixels.
 */
constexpr uint16_t operator""_in(unsigned long long inches) {
	return inches * GIGA_DISPLAY_PPI;
}

/**
 * @brief The custom units operator for view width percent.
 *
 * This operator allows for writing sizes like `12.5_vw`,
 * which will automatically be converted to pixels at compile time.
 *
 * @param view_width_percent The size in view width percent.
 * @return The size in pixels.
 */
constexpr uint16_t operator""_vw(long double view_width_percent) {
	return view_width_percent * GIGA_DISPLAY_W_PX / 100;
}

/**
 * @brief The custom units operator for view width percent.
 *
 * This operator allows for writing sizes like `25_vw`,
 * which will automatically be converted to pixels at compile time.
 *
 * @param view_width_percent The size in view width percent.
 * @return The size in pixels.
 */
constexpr uint16_t operator""_vw(unsigned long long view_width_percent) {
	return view_width_percent * GIGA_DISPLAY_W_PX / 100;
}

/**
 * @brief The custom units operator for view height percent.
 *
 * This operator allows for writing sizes like `12.5_vh`,
 * which will automatically be converted to pixels at compile time.
 *
 * @param view_height_percent The size in view height percent.
 * @return The size in pixels.
 */
constexpr uint16_t operator""_vh(long double view_height_percent) {
	return view_height_percent * GIGA_DISPLAY_H_PX / 100;
}

/**
 * @brief The custom units operator for view height percent.
 *
 * This operator allows for writing sizes like `25_vh`,
 * which will automatically be converted to pixels at compile time.
 *
 * @param view_height_percent The size in view height percent.
 * @return The size in pixels.
 */
constexpr uint16_t operator""_vh(unsigned long long view_height_percent) {
	return view_height_percent * GIGA_DISPLAY_H_PX / 100;
}

/**
 * @brief The custom units operator for points.
 *
 * This operator allows for writing sizes like `12.5_pt`,
 * which will automatically be converted to pixels at compile time.
 *
 * @param points The size in points.
 * @return The size in pixels.
 */
constexpr uint16_t operator""_pt(long double points) {
	// 1 point = 1/72 inch
	return points * GIGA_DISPLAY_PPI / 72;
}

/**
 * @brief The custom units operator for points.
 *
 * This operator allows for writing sizes like `12_pt`,
 * which will automatically be converted to pixels at compile time.
 *
 * @param points The size in points.
 * @return The size in pixels.
 */
constexpr uint16_t operator""_pt(unsigned long long points) {
	// 1 point = 1/72 inch
	return points * GIGA_DISPLAY_PPI / 72;
}
