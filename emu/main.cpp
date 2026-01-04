#include <cstring>
#include <define.h>
#include <iostream>
#include <raylib.h>

#include "Arduino.h"
#include "ino.hpp"
#include "src/ui.hpp"

void DrawOverlayText(const char *text, int posX, int posY, int fontSize = 20) {
	DrawText(text, posX - 1, posY - 1, fontSize, {0, 0, 0, 255});
	DrawText(text, posX + 1, posY - 1, fontSize, {0, 0, 0, 255});
	DrawText(text, posX - 1, posY + 1, fontSize, {0, 0, 0, 255});
	DrawText(text, posX + 1, posY + 1, fontSize, {0, 0, 0, 255});
	DrawText(text, posX, posY, fontSize, {255, 255, 255, 255});
}

int main() {
	InitWindow(GIGA_DISPLAY_W_PX * WINDOW_SCALE, GIGA_DISPLAY_H_PX * WINDOW_SCALE, WINDOW_TITLE);

	// Target the same max frequency as the native UI would render in.
	SetTargetFPS(1000 / UI_RENDER_FREQUENCY);

	setup();

	bool showBounds = false;
	bool showOverlay = true;

	while (!WindowShouldClose()) {
		if (showOverlay) {
			DrawOverlayText("[H] Toggle this help text", 0, 0);
			DrawOverlayText("[B] Toggle bounding boxes", 0, 20);
			DrawOverlayText("[R] Force re-render", 0, 40);

			DrawRectangle(0, ui::height() - 20, ui::width(), ui::height(), {0, 0, 0, 255});
			char buf[2048];
			sprintf(buf, "Time: %ldms", millis());
			DrawOverlayText(buf, 0, ui::height() - 20); // GIGA_DISPLAY_H_PX * WINDOW_SCALE - 100);
		}

		loop();

		if (IsKeyPressed(KEY_H)) {
			showOverlay = !showOverlay;
			ui::showBoundingBoxes(showBounds); // Force re-render
			std::cout << "INFO: " << (showBounds ? "Enabled" : "Disabled") << " text overlay" << std::endl;
		}

		if (IsKeyPressed(KEY_B)) {
			showBounds = !showBounds;
			ui::showBoundingBoxes(showBounds);
			std::cout << "INFO: " << (showBounds ? "Enabled" : "Disabled") << " bounding boxes" << std::endl;
		}

		if (IsKeyPressed(KEY_R)) {
			ui::showBoundingBoxes(showBounds);
			std::cout << "INFO: Forced re-render" << std::endl;
		}
	}

	CloseWindow();
}
