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

void begin(bool require_touch = false);
void setRotation(rotation_t rotation);
bool rotationChanged();
void finalizeRotation();

void drawPixel(coord_t x, coord_t y, color_t color);
void fillScreen(color_t color);
void byteSwap();
void drawFastVLine(coord_t x, coord_t y, coord_t h, color_t color);
void drawFastHLine(coord_t x, coord_t y, coord_t w, color_t color);
color_t getPixel(coord_t x, coord_t y);
color_t *getBuffer();
color_t *hasBuffer();

void startWrite();
void endWrite();

void setCursor(coord_t x, coord_t y);
void setTextSize(uint8_t size);
void setTextColor(color_t color);
void setTextWrap(bool wrap);
void print(const String &str);

uisize_t width();
uisize_t height();

Event getTouchEvent();

void fillRoundRect(coord_t x, coord_t y, coord_t width, coord_t height, radius_t radius, color_t color);

void drawBitmap(coord_t x, coord_t y, const uint8_t bitmap[], coord_t w, coord_t h, color_t color);
void drawBitmap(coord_t x, coord_t y, const uint8_t bitmap[], coord_t w, coord_t h, color_t color, color_t bg);
void drawBitmap(coord_t x, coord_t y, uint8_t *bitmap, coord_t w, coord_t h, color_t color);
void drawBitmap(coord_t x, coord_t y, uint8_t *bitmap, coord_t w, coord_t h, color_t color, color_t bg);
void drawXBitmap(coord_t x, coord_t y, const uint8_t bitmap[], coord_t w, coord_t h, color_t color);
void drawGrayscaleBitmap(coord_t x, coord_t y, const uint8_t bitmap[], coord_t w, coord_t h);
void drawGrayscaleBitmap(coord_t x, coord_t y, uint8_t *bitmap, coord_t w, coord_t h);
void drawGrayscaleBitmap(coord_t x, coord_t y, const uint8_t bitmap[], const uint8_t mask[], coord_t w, coord_t h);
void drawGrayscaleBitmap(coord_t x, coord_t y, uint8_t *bitmap, uint8_t *mask, coord_t w, coord_t h);
void drawRGBBitmap(coord_t x, coord_t y, const color_t bitmap[], coord_t w, coord_t h);
void drawRGBBitmap(coord_t x, coord_t y, color_t *bitmap, coord_t w, coord_t h);
void drawRGBBitmap(coord_t x, coord_t y, const color_t bitmap[], const uint8_t mask[], coord_t w, coord_t h);
void drawRGBBitmap(coord_t x, coord_t y, color_t *bitmap, uint8_t *mask, coord_t w, coord_t h);

} // namespace ui
