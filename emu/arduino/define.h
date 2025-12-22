#pragma once

#define GIGA_DISPLAY_W_PX 480
#define GIGA_DISPLAY_H_PX 800
#ifndef WINDOW_TITLE
#define WINDOW_TITLE "GigaWidgets Emulator"
#endif
#ifndef WINDOW_SCALE
#define WINDOW_SCALE 1
#endif

#include <cinttypes>
#include <raylib.h>

Color rgb(uint16_t color565);
