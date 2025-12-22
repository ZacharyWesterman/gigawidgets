#include "Arduino_GigaDisplayTouch.h"

Arduino_GigaDisplayTouch::Arduino_GigaDisplayTouch() {}

Arduino_GigaDisplayTouch::~Arduino_GigaDisplayTouch() {}

bool Arduino_GigaDisplayTouch::begin() {
	return true;
}

uint8_t Arduino_GigaDisplayTouch::getTouchPoints(GDTpoint_t *points) {
	return 0;
}
