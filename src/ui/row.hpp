/// @file row.hpp
#pragma once

#include "collection.hpp"

namespace ui {

class Row : public Collection {
	uisize_t minimumWidth = 0;
	align_t childAlignment = ALIGN_LEFT;

	void calcChildBounds(int index);

public:
	using Collection::Collection;

	bool update(time_t time) override;

	void push(Widget *const child) override;

	void setMinWidth(uisize_t minWidth);
	void setChildAlign(align_t align);

	inline uisize_t getMinWidth() const {
		return minimumWidth;
	}

	inline align_t getChildAlign() const {
		return childAlignment;
	}
};

} // namespace ui
