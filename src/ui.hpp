/// @file ui.hpp
#pragma once

#include "ui/blink.hpp"
#include "ui/body.hpp"
#include "ui/button.hpp"
#include "ui/collection.hpp"
#include "ui/column.hpp"
#include "ui/core/display.hpp"
#include "ui/core/units.hpp"
#include "ui/image.hpp"
#include "ui/text.hpp"

#ifndef UI_RENDER_FREQUENCY
// Refresh at most every 50ms
#define UI_RENDER_FREQUENCY 50
#endif

namespace ui {

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

} // namespace ui
