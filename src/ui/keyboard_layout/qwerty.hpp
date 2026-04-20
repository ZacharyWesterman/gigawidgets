/// @file querty.hpp
#pragma once
#include "../keyboard_layout.hpp"

namespace ui {
namespace layout {

struct QwertyLayout : public KeyboardLayout {
	const char *row1(bool upper, bool alt) const override;
	const char *row2(bool upper, bool alt) const override;
	const char *row3(bool upper, bool alt) const override;
};

static const QwertyLayout qwerty;

} // namespace layout
} // namespace ui
