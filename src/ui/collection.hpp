/// @file collection.hpp
#pragma once

#include "containers/multi_child_widget.hpp"

namespace ui {

/**
 * @brief A container widget for displaying a list of arbitrarily-positioned child widgets.
 */
class Collection : public MultiChildWidget {
	/// @brief The size of this container widget.
	Size widgetSize;

public:
	/**
	 * @brief Construct a collection.
	 * @param size The size of this container widget.
	 * @param pos The position of this widget relative to its parent.
	 * @param align The alignment of this widget relative to its parent.
	 * @param padding The padding to apply to the child widget.
	 */
	Collection(const Size &size, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	Size size() const override;

	DERIVE_EVENT_HANDLERS(Collection)
};

} // namespace ui
