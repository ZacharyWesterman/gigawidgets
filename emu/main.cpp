#include <define.h>
#include <raylib.h>

#include "ino.hpp"

int main() {
	InitWindow(GIGA_DISPLAY_W_PX * WINDOW_SCALE, GIGA_DISPLAY_H_PX * WINDOW_SCALE, WINDOW_TITLE);
	SetTargetFPS(30);

	setup();

	while (!WindowShouldClose()) {
		loop();
	}

	CloseWindow();
}
