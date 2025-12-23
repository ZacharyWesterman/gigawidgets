/// @file event.hpp
#pragma once

#include <ctime>

#include "coords.hpp"

namespace ui {

/**
 * @brief The various touchscreen event types.
 *
 * These events only include those passed directly from the touchscreen
 * to the UI, and so do not include the onblur event.
 */
enum event_t {
	EVENT_PRESS,
	EVENT_RELEASE,
	EVENT_HOLD,
};

/**
 * @brief A touchscreen event.
 */
struct Event {
	/// @brief True if this event should be handled, false otherwise.
	bool triggered = false;

	/// @brief The touchscreen event type.
	event_t type;

	/// @brief The number of distinct points on the screen that were touched.
	uint8_t contacts;

	/// @brief A list of coordinates corresponding to each touch point, accounting for screen rotation.
	Coords coords[5];

	/// @brief The number of milliseconds that the screen has been pressed continuously.
	time_t timeHeld;
};

} // namespace ui
