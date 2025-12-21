/// @file column.hpp
#pragma once

#include "collection.hpp"

namespace ui {

class Column : public Collection {
	uisize_t minimumHeight = 0;
	align_t childAlignment = ALIGN_TOP;

	void calcChildBounds(int index);

public:
	using Collection::Collection;

	bool update(time_t time) override;

	void push(Widget *const child) override;

	void setMinHeight(uisize_t minHeight);
	void setChildAlign(align_t align);

	inline uisize_t getMinHeight() const {
		return minimumHeight;
	}

	inline align_t getChildAlign() const {
		return childAlignment;
	}
};

} // namespace ui
