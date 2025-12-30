#include <define.h>
#include <iostream>
#include <raylib.h>

#include "ino.hpp"
#include "src/ui.hpp"

int main() {
	InitWindow(GIGA_DISPLAY_W_PX * WINDOW_SCALE, GIGA_DISPLAY_H_PX * WINDOW_SCALE, WINDOW_TITLE);
	SetTargetFPS(30);

	setup();

	bool showBounds = false;

	while (!WindowShouldClose()) {
		DrawText("[B] Toggle bounding boxes", 0, 0, 1, {255, 255, 255, 255});

		loop();

		if (IsKeyPressed(KEY_B)) {
			showBounds = !showBounds;
			ui::showBoundingBoxes(showBounds);
			std::cout << "INFO: " << (showBounds ? "Enabled" : "Disabled") << " bounding boxes" << std::endl;
		}
	}

	CloseWindow();
}
