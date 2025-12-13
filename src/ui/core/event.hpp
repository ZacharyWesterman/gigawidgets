/// @file event.hpp
#pragma once

#include "coords.hpp"

namespace ui {

enum event_t {
	EVENT_PRESS,
	EVENT_RELEASE,
	EVENT_HOLD,
};

struct Event {
	bool triggered = false;
	event_t type;
	uint8_t contacts;
	Coords coords[5];
	time_t timeHeld;
};

} // namespace ui
