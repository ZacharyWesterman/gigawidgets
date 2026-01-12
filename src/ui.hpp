/// @file ui.hpp
#pragma once

#include "ui/blink.hpp"
#include "ui/body.hpp"
#include "ui/collection.hpp"
#include "ui/column.hpp"
#include "ui/core/display.hpp"
#include "ui/core/units.hpp"
#include "ui/image.hpp"
#include "ui/input.hpp"
#include "ui/panel.hpp"
#include "ui/row.hpp"
#include "ui/text.hpp"

#include <functional>

#ifndef UI_RENDER_FREQUENCY
// Refresh at most every 50ms
#define UI_RENDER_FREQUENCY 50
#endif

namespace ui {

/**
 * @typedef callback_t
 * @brief A callback function that takes no arguments and returns nothing.
 */
typedef std::function<void()> callback_t;

/**
 * @brief Set the root widget for the UI to render.
 * @param root The topmost widget where rendering starts.
 */
void setRoot(Widget *const root);

/**
 * @brief Update all UI elements and re-render any areas that need it.
 * @param block If true, save CPU usage by blocking until it's time to render the screen. If false, return immediately if it's not time to render yet.
 */
void render(bool block = true);

#ifdef DEBUG
/**
 * @brief Toggle whether bounding boxes are displayed for all widgets.
 * @param enable If true, show bounding boxes. If false, hide bounding boxes.
 * @note This function is only available in debug builds.
 */
void showBoundingBoxes(bool enable);
#endif

/**
 * @brief Schedule a function to run after a delay.
 *
 * Callback functions will be postponed for *at least* the number
 * of milliseconds specified, but may wait slightly longer,
 * depending on refresh rate.
 *
 * @param callback The function to run.
 * @param timeout The number of milliseconds to wait.
 */
void setTimeout(callback_t callback, time_t timeout);

} // namespace ui
