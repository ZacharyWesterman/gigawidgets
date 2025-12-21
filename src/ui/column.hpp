/// @file column.hpp
#pragma once

#include "collection.hpp"
#include "core/spacing.hpp"

namespace ui {

class Column : public Collection {
	spacing_t spacing;

public:
	using Collection::Collection;

	void addChild(Widget *const child) override;
};

} // namespace ui
