#include <Arduino.h>

#include "ui.hpp"

#ifdef EMULATE
#include <raylib.h>
#endif

namespace ui {

static Widget *prevRoot = nullptr;
static Widget *rootNode = nullptr;
static time_t lastRender = 0;

void setRoot(Widget *const root) {
	if (prevRoot) {
		delete prevRoot;
		prevRoot = nullptr;
	}

	if (rootNode) {
		prevRoot = rootNode;
	} else {
		ui::begin();
	}
	rootNode = root;
}

void render(bool block) {

#ifdef EMULATE
	static auto r = [](bool block) {
#endif
		if (prevRoot) {
			delete prevRoot;
			prevRoot = nullptr;
		}

		auto currentTime = millis();
		const auto elapsed = currentTime - lastRender;
		if (block) {
			if (elapsed < UI_RENDER_FREQUENCY) {
				delay(UI_RENDER_FREQUENCY - elapsed);
			}
			currentTime = millis();
		} else if (elapsed < UI_RENDER_FREQUENCY && elapsed >= 0 && lastRender != 0) {
			return;
		}
		lastRender = currentTime;

		if (!rootNode) {
			return;
		}

		const auto event = getTouchEvent();
		if (event.triggered) {
			rootNode->handleEvent(event);
		}

		const auto rChanged = rotationChanged();
		if (rootNode->update(millis()) || rootNode->redrawRequested() || rChanged) {
			ui::endWrite();
			rootNode->draw();
		}

		rootNode->drawDone();
		if (rChanged) {
			finalizeRotation();
		}

#ifdef EMULATE
	};

	EndDrawing();
	r(block);
	BeginDrawing();
#endif
}

} // namespace ui
