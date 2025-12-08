#include "element.hpp"
#include "display.hpp"

namespace ui {

Element::Element(const Position &pos, const Alignment &align, const Padding &padding) : parent(nullptr), pos(pos), align(align), pressed(false), padding(padding), initialRender(false), redrawParent(true), redrawSelf(true) {}

Element::~Element() {}

bool Element::update(time_t time_ms) {
	if (initialRender) {
		return rotationChanged() || redrawSelf;
	}

	initialRender = true;
	return true;
}

void Element::drawDone() {
	redrawParent = false;
	redrawSelf = false;
}

void Element::setParent(Element *parent) {
	this->parent = parent;
}

Bounds Element::parentBounds() const {
	if (parent) {
		auto b = parent->bounds();

		b.min.x += parent->padding.left;
		b.max.x -= parent->padding.right;
		b.min.y += parent->padding.top;
		b.max.y -= parent->padding.bottom;

		return b;
	}

	Coords min = {0, 0};
	Coords max = {ui::width(), ui::height()};

	return {min, max};
}

Bounds Element::bounds() const {
	const auto sz = size();
	auto b = parentBounds();

	Coords positionOnParent = {
		(b.max.x - b.min.x) * pos.x + b.min.x,
		(b.max.y - b.min.y) * pos.y + b.min.y,
	};

	// Adjust position based on alignment and parent padding

	if (align.v == ALIGN_CENTER) {
		b.min.y = positionOnParent.y - sz.y / 2;
		b.max.y = positionOnParent.y + sz.y / 2;
	} else if (align.v == ALIGN_BOTTOM) {
		b.min.y = positionOnParent.y - sz.y;
		b.max.y = positionOnParent.y;
	} else {
		// Top-align is default.
		b.min.y = positionOnParent.y;
		b.max.y = positionOnParent.y + sz.y;
	}

	if (align.h == ALIGN_CENTER) {
		b.min.x = positionOnParent.x - sz.x / 2;
		b.max.x = positionOnParent.x + sz.x / 2;
	} else if (align.h == ALIGN_RIGHT) {
		b.min.x = positionOnParent.x - sz.x;
		b.max.x = positionOnParent.x;
	} else {
		// Left-align is default
		b.min.x = positionOnParent.x;
		b.max.x = positionOnParent.x + sz.x;
	}

	return b;
}

bool Element::handleEvent(const Event &event) {
	const auto b = bounds();

	if (!bounds().contains(event.coords[0])) {
		// If this element *was* pressed but user slid their finger off,
		// trigger the blur event.
		if (pressed) {
			if (callbackBlur) {
				callbackBlur(*this);
			}
			pressed = false;
			return true;
		}

		return false;
	}

	switch (event.type) {
	case EVENT_PRESS:
		if (callbackPress) {
			callbackPress(*this);
		}
		pressed = true;
		break;
	case EVENT_HOLD:
		if (event.timeHeld > ONHOLD_EVENT_DEBOUNCE && callbackHold) {
			callbackHold(*this, event.timeHeld);
		}
		break;
	case EVENT_RELEASE:
		if (callbackRelease) {
			callbackRelease(*this);
		}
		if (pressed && callbackBlur) {
			callbackBlur(*this);
		}
		pressed = false;
		break;
	}

	return true;
}

void Element::onclick(std::function<void(Element &)> callback) {
	callbackRelease = callback;
};

void Element::onclick(std::function<void()> callback) {
	callbackRelease = [callback](Element &) { callback(); };
}

void Element::onpress(std::function<void(Element &)> callback) {
	callbackPress = callback;
}

void Element::onpress(std::function<void()> callback) {
	callbackPress = [callback](Element &) { callback(); };
}

void Element::onblur(std::function<void(Element &)> callback) {
	callbackBlur = callback;
}

void Element::onblur(std::function<void()> callback) {
	callbackBlur = [callback](Element &) { callback(); };
}

void Element::onhold(std::function<void(Element &, unsigned long)> callback) {
	callbackHold = callback;
}

void Element::onhold(std::function<void(unsigned long)> callback) {
	callbackHold = [callback](Element &, time_t time_ms) { callback(time_ms); };
}

void Element::onrelease(std::function<void(Element &)> callback) {
	callbackRelease = callback;
}

void Element::onrelease(std::function<void()> callback) {
	callbackRelease = [callback](Element &) { callback(); };
}

void Element::click() {
	if (callbackRelease) {
		callbackRelease(*this);
	}
}

void Element::press() {
	if (callbackPress) {
		callbackPress(*this);
	}
}

void Element::blur() {
	if (callbackRelease) {
		callbackRelease(*this);
	}
}

void Element::release() {
	if (callbackRelease) {
		callbackRelease(*this);
	}
}

void Element::hold(time_t time) {
	if (callbackHold) {
		callbackHold(*this, time);
	}
}

} // namespace ui
