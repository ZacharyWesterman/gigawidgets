#pragma once

#include "ui/blink.hpp"
#include "ui/body.hpp"
#include "ui/button.hpp"
#include "ui/core/display.hpp"
#include "ui/core/units.hpp"
#include "ui/image.hpp"
#include "ui/text.hpp"

#ifndef UI_RENDER_FREQUENCY
// Refresh at most every 50ms
#define UI_RENDER_FREQUENCY 50
#endif

namespace ui {

void setRoot(Widget *const root);
void render(bool block = true);

} // namespace ui
