#include <Arduino.h>

#include "ui.hpp"

#ifdef EMULATE
#include <raylib.h>
#endif

namespace ui {

static Widget *prevRoot = nullptr;
static Widget *rootNode = nullptr;
static time_t lastRender = 0;

#ifdef DEBUG
bool boundingBoxesVisble = false;
#endif

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

#ifdef DEBUG
		if (boundingBoxesVisble) {
			rootNode->drawBoundingBox(currentTime);
			ui::endWrite();
		}
#endif

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

#ifdef DEBUG
void showBoundingBoxes(bool enable) {
	boundingBoxesVisble = enable;
	// A bit of a hack to force a re-render. Fine since this is for debug builds only.
	auto r = getRotation();
	setRotation((rotation_t)(r + 2 % 4));
	if (rootNode) {
		ui::endWrite();
		rootNode->draw();
	}
	setRotation(r);
}
#endif

} // namespace ui
