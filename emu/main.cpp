#include <raylib.h>

#include "ino.hpp"

#define GIGA_DISPLAY_W_PX 480
#define GIGA_DISPLAY_H_PX 800
#ifndef WINDOW_TITLE
#define WINDOW_TITLE "GigaWidgets Emulator"
#endif
#ifndef WINDOW_SCALE
#define WINDOW_SCALE 1
#endif

int main() {
	InitWindow(GIGA_DISPLAY_W_PX * WINDOW_SCALE, GIGA_DISPLAY_H_PX * WINDOW_SCALE, WINDOW_TITLE);

	setup();

	while (!WindowShouldClose()) {
		loop();
	}

	CloseWindow();
}
