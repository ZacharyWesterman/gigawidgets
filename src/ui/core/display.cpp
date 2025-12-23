#include <Arduino_GigaDisplayTouch.h>
#include <Arduino_GigaDisplay_GFX.h>

#include "display.hpp"

#define LED_RED 86
#define LED_GREEN 87
#define LED_BLUE 88

void builtinLedRed() {
	digitalWrite(LED_RED, LOW);
	digitalWrite(LED_GREEN, HIGH);
	digitalWrite(LED_BLUE, HIGH);
}

void builtinLedOff() {
	digitalWrite(LED_RED, HIGH);
	digitalWrite(LED_GREEN, HIGH);
	digitalWrite(LED_BLUE, HIGH);
}

namespace ui {

static GigaDisplay_GFX display;
static Arduino_GigaDisplayTouch touch;
static bool touchEnabled = false;

static bool pressed = false;
static unsigned long pressStarted = 0;
static Event event = {};

static rotation_t lastRotation = ROT_0_DEG;
static bool uiRotationChanged = false;

void begin(bool require_touch) {
	display.begin();
	display.fillScreen(0); // Initialize by filling with black screen.

	touchEnabled = touch.begin();
	if (!touchEnabled && require_touch) {
		Serial.println("FATAL ERROR: Unable to initialize touchscreen!");

		// Blink red LED to indicate fatal error
		while (true) {
			builtinLedRed();
			delay(500);
			builtinLedOff();
			delay(500);
		}
	}
}

void setRotation(rotation_t rotation) {
	if (lastRotation != rotation) {
		lastRotation = rotation;
		uiRotationChanged = true;
		display.setRotation(rotation);
	}
}

bool rotationChanged() {
	return uiRotationChanged;
}

void finalizeRotation() {
	uiRotationChanged = false;
}

void drawPixel(coord_t x, coord_t y, color_t color) {
	display.drawPixel(x, y, color);
}

void fillScreen(color_t color) {
	display.fillScreen(color);
}

void drawFastVLine(coord_t x, coord_t y, coord_t h, color_t color) {
	display.drawFastVLine(x, y, h, color);
}

void drawFastHLine(coord_t x, coord_t y, coord_t w, color_t color) {
	display.drawFastHLine(x, y, w, color);
}

color_t getPixel(coord_t x, coord_t y) {
	return display.getPixel(x, y);
}

color_t *getBuffer() {
	return display.getBuffer();
}

color_t *hasBuffer() {
	return display.hasBuffer();
}

void endWrite() {
	display.endWrite();
}

void setCursor(coord_t x, coord_t y) {
	display.setCursor(x, y);
}
void setTextSize(uint8_t size) {
	display.setTextSize(size);
}
void setTextColor(color_t color) {
	display.setTextColor(color);
}
void setTextWrap(bool wrap) {
	display.setTextWrap(wrap);
}
void print(const String &str) {
	display.print(str);
}

uisize_t width() {
	return display.width();
}

uisize_t height() {
	return display.height();
}

Event getTouchEvent() {
	if (touchEnabled) {
		GDTpoint_t points[5];
		event.contacts = touch.getTouchPoints(points);
		event.triggered = false;

		if (event.contacts > 0) {
			event.triggered = true;
			for (int i = 0; i < event.contacts; i++) {
				auto x = points[i].x;
				auto y = points[i].y;

#ifndef EMULATE
				// Account for screen rotation
				switch ((rotation_t)display.getRotation()) {
				case ROT_270_DEG:
					std::swap(x, y);
					x = ui::width() - x;
					break;
				case ROT_180_DEG:
					x = ui::width() - x;
					y = ui::height() - y;
					break;
				case ROT_90_DEG:
					std::swap(x, y);
					y = ui::height() - y;
					break;
				}
#endif

				event.coords[i].x = x;
				event.coords[i].y = y;
			}

			if (!pressed) {
				pressed = true;
				pressStarted = millis();
				event.type = EVENT_PRESS;
			} else {
				event.timeHeld = millis() - pressStarted;
				event.type = EVENT_HOLD;
			}
		} else if (pressed) {

			pressed = false;
			event.triggered = true;
			event.type = EVENT_RELEASE;
		}
	}

	return event;
}

void fillRoundRect(coord_t x, coord_t y, coord_t width, coord_t height, radius_t radius, color_t color) {
	display.fillRoundRect(x, y, width, height, radius, color);
}

void drawBitmap(coord_t x, coord_t y, uint8_t *bitmap, coord_t w, coord_t h, color_t color) {
	display.drawBitmap(x, y, bitmap, w, h, color);
}

void drawRGBBitmap(coord_t x, coord_t y, color_t *bitmap, coord_t w, coord_t h) {
	display.drawRGBBitmap(x, y, bitmap, w, h);
}

void drawRGBBitmap(coord_t x, coord_t y, color_t *bitmap, uint8_t *mask, coord_t w, coord_t h) {
	display.drawRGBBitmap(x, y, bitmap, mask, w, h);
}

} // namespace ui
