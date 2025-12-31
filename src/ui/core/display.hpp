/// @file display.hpp
/// This file contains low-level functions for rendering directly to the screen.
#pragma once

#include <Arduino.h>
#include <cinttypes>

#include "color.hpp"
#include "coords.hpp"
#include "event.hpp"
#include "radius.hpp"
#include "rotation.hpp"
#include "size.hpp"

namespace ui {

/**
 * @brief Initialize the screen.
 * @param require_touch If true and the touchscreen failed to initialize, spit out a fatal error and halt execution.
 */
void begin(bool require_touch = false);

/**
 * @brief Set the screen rotation.
 * @param rotation The new screen rotation; one of 4 cardinal directions.
 */
void setRotation(rotation_t rotation);

/**
 * @brief Get the current screen rotation.
 * @return A value indicating the screen rotation.
 */
rotation_t getRotation();

/**
 * @brief Check if the screen rotation has changed since the last render cycle.
 * @return True if the rotation has changed, false otherwise.
 */
bool rotationChanged();

/**
 * @brief After a render cycle has completed, set the screen rotation to not changed.
 */
void finalizeRotation();

/**
 * @brief Render a pixel to the screen, accounting for rotation.
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param color The color of the pixel.
 */
void drawPixel(coord_t x, coord_t y, color_t color);

/**
 * @brief Fill the screen with a color.
 * @param color The color to fill.
 */
void fillScreen(color_t color);

/**
 * @brief Draw a hardware-accelerated vertical line.
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param h The height of the line, in pixels.
 * @param color The color of the line.
 */
void drawFastVLine(coord_t x, coord_t y, coord_t h, color_t color);

/**
 * @brief Draw a hardware-accelerated horizontal line.
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param w The length of the line, in pixels.
 * @param color The color of the line.
 */
void drawFastHLine(coord_t x, coord_t y, coord_t w, color_t color);

/**
 * @brief Flush data to the screen.
 */
void endWrite();

/**
 * @brief Set the current position for rendering text.
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 */
void setCursor(coord_t x, coord_t y);

/**
 * @brief Set the scaling factor for rendering text.
 * @param size The scaling factor.
 */
void setTextSize(uint8_t size);

/**
 * @brief Set the color of rendered text.
 * @param color The text color.
 */
void setTextColor(color_t color);

/**
 * @brief Set whether text wraps.
 * @param wrap If true, wrap text. If false, do not wrap.
 */
void setTextWrap(bool wrap);

/**
 * @brief Write text to the screen.
 * @param str The string to write.
 */
void print(const String &str);

/**
 * @brief Get the screen width, adjusted for rotation.
 * @return The screen width.
 */
uisize_t width();

/**
 * @brief Get the screen height, adjusted for rotation.
 * @return The screen height.
 */
uisize_t height();

/**
 * @brief Check for a touchscreen event.
 * @return The current touchscreen event, including whether one was triggered.
 */
Event getTouchEvent();

/**
 * @brief Draw a filled rectangle with rounded corners.
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param width The horizontal size of the rectangle.
 * @param height The vertical size of the rectangle.
 * @param radius The radius of the curved corners.
 * @param color The color of the rectangle.
 */
void fillRoundRect(coord_t x, coord_t y, coord_t width, coord_t height, radius_t radius, color_t color);

/**
 * @brief Draw a rectangle.
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param width The horizontal size of the rectangle.
 * @param height The vertical size of the rectangle.
 * @param color The color of the rectangle.
 */
void drawRect(coord_t x, coord_t y, coord_t width, coord_t height, color_t color);

/**
 * @brief Draw a single-color bitmap.
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param bitmap The bitmap data to render.
 * @param w The horizontal size of the bitmap.
 * @param h The vertical size of the bitmap.
 * @param color The color to render non-zero pixels as.
 */
void drawBitmap(coord_t x, coord_t y, uint8_t *bitmap, coord_t w, coord_t h, color_t color);

/**
 * @brief Draw an RGB bitmap without transparency.
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param bitmap The bitmap data to render.
 * @param w The horizontal size of the bitmap.
 * @param h The vertical size of the bitmap.
 */
void drawRGBBitmap(coord_t x, coord_t y, color_t *bitmap, coord_t w, coord_t h);

/**
 * @brief Draw an RGB bitmap with a transparency mask.
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param bitmap The bitmap data to render.
 * @param mask The 1-bit transparency mask.
 * @param w The horizontal size of the bitmap.
 * @param h The vertical size of the bitmap.
 */
void drawRGBBitmap(coord_t x, coord_t y, color_t *bitmap, uint8_t *mask, coord_t w, coord_t h);

} // namespace ui
