/// @file keyboard_layout.class
#pragma once

namespace ui {
namespace layout {

struct KeyboardLayout {
	virtual const char *row1(bool upper, bool alt) const = 0;
	virtual const char *row2(bool upper, bool alt) const = 0;
	virtual const char *row3(bool upper, bool alt) const = 0;
};

} // namespace layout
} // namespace ui
