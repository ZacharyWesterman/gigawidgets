#include "Arduino_GigaDisplayTouch.h"

#include <raylib.h>

Arduino_GigaDisplayTouch::Arduino_GigaDisplayTouch() {}

Arduino_GigaDisplayTouch::~Arduino_GigaDisplayTouch() {}

bool Arduino_GigaDisplayTouch::begin() {
	return true;
}

uint8_t Arduino_GigaDisplayTouch::getTouchPoints(GDTpoint_t *points) {
	// Only supports a single touch point.

	if (IsMouseButtonDown(0)) {
		points[0].x = GetMouseX();
		points[0].y = GetMouseY();
		return 1;
	}

	return 0;
}
