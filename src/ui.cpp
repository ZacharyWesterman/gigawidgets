#include <Arduino.h>
#include <algorithm>
#include <vector>

#include "ui.hpp"

#ifdef EMULATE
#include <raylib.h>
#endif

namespace ui {

struct TimedCallback {
	std::function<void()> method;
	time_t endTime;
};

std::vector<TimedCallback> timedCallbacks;

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

		// Check timeout callbacks, executing and then removing any that are due.
		// Note that callback execution has a resolution of at most the screen refresh rate.
		auto callbackReady = [currentTime](const TimedCallback &callback) {
			if (callback.endTime <= currentTime) {
				callback.method();
				return true;
			}
			return false;
		};
		auto removeIf = std::remove_if(timedCallbacks.begin(), timedCallbacks.end(), callbackReady);
		timedCallbacks.erase(removeIf, timedCallbacks.end());

		if (!rootNode) {
			return;
		}

		auto event = getTouchEvent();
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

void setTimeout(std::function<void()> callback, time_t timeout) {
	timedCallbacks.push_back({
		callback,
		millis() + timeout,
	});
}

} // namespace ui
