#include <raylib.h>

#include "Arduino_GigaDisplay_GFX.h"

#define GIGA_DISPLAY_W_PX 480
#define GIGA_DISPLAY_H_PX 800
#ifndef WINDOW_TITLE
#define WINDOW_TITLE "GigaWidgets Emulator"
#endif
#ifndef WINDOW_SCALE
#define WINDOW_SCALE 1
#endif

Color rgb(uint16_t color565) {
	uint8_t r = color565 >> 8;
	uint8_t g = color565 >> 3 & 0xff;
	uint8_t b = color565 << 3 & 0xff;
	return {r, g, b, 255};
}

void GigaDisplay_GFX::begin() {
	BeginDrawing();
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
	DrawLine(x * WINDOW_SCALE, y * WINDOW_SCALE, x * WINDOW_SCALE, (y + h) * WINDOW_SCALE, rgb(color));
}

void GigaDisplay_GFX::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
	DrawLine(x * WINDOW_SCALE, y * WINDOW_SCALE, (x + w) * WINDOW_SCALE, y * WINDOW_SCALE, rgb(color));
}

uint16_t GigaDisplay_GFX::getPixel(int16_t x, int16_t y) {
	return 0; // Dummy, returns black always.
}

void GigaDisplay_GFX::endWrite() {
	EndDrawing();
	BeginDrawing();
}
