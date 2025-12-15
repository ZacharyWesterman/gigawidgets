/// @file column.hpp
#pragma once

#include "collection.hpp"

namespace ui {

class Column : public Collection {
	bool expand;

public:
	using Collection::Collection;

	void addChild(Widget *const child) override;
};

} // namespace ui
