#include <raylib.h>

#include "Arduino_GigaDisplay_GFX.h"
#include "define.h"

GigaDisplay_GFX::GigaDisplay_GFX() : Adafruit_GFX(GIGA_DISPLAY_W_PX * WINDOW_SCALE, GIGA_DISPLAY_H_PX * WINDOW_SCALE) {}

GigaDisplay_GFX::~GigaDisplay_GFX() {}

void GigaDisplay_GFX::begin() {
	// BeginDrawing();
}

void GigaDisplay_GFX::fillScreen(uint16_t color) {
	ClearBackground(rgb(color));
}

void GigaDisplay_GFX::drawPixel(int16_t x, int16_t y, uint16_t color) {
	if (WINDOW_SCALE > 1) {
		DrawRectangle(x * WINDOW_SCALE, y * WINDOW_SCALE, WINDOW_SCALE, WINDOW_SCALE, rgb(color));
	} else {
		DrawPixel(x * WINDOW_SCALE, y * WINDOW_SCALE, rgb(color));
	}
}

void GigaDisplay_GFX::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
	DrawLine(x * WINDOW_SCALE, y * WINDOW_SCALE, x * WINDOW_SCALE, (y + h - 1) * WINDOW_SCALE, rgb(color));
}

void GigaDisplay_GFX::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
	DrawLine(x * WINDOW_SCALE, y * WINDOW_SCALE, (x + w - 1) * WINDOW_SCALE, y * WINDOW_SCALE, rgb(color));
}

uint16_t GigaDisplay_GFX::getPixel(int16_t x, int16_t y) {
	return 0; // Dummy, returns black always.
}

void GigaDisplay_GFX::startWrite() {
	// BeginDrawing();
}

void GigaDisplay_GFX::endWrite() {
	// BeginDrawing();
	// EndDrawing();
}
