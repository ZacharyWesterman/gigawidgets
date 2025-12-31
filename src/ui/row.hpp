/// @file row.hpp
#pragma once

#include "collection.hpp"

namespace ui {

/**
 * @brief A container widget that horizontally organizes its children into a structured row.
 */
class Row : public Collection {
	/// @brief The minimum width of each cell in the row.
	uisize_t minimumWidth = 0;
	/// @brief Where to start when displaying child widgets; on the left, or right.
	align_t childAlignment = ALIGN_LEFT;

	/**
	 * @brief Calculate and assign the bounds of a child widget at the given index.
	 * @param index The index of the child widget.
	 */
	void calcChildBounds(int index);

public:
	using Collection::Collection;

	bool update(time_t time) override;

	void push(Widget *const child) override;

	/**
	 * @brief Set the minimum width of each cell in the row.
	 * @param minWidth The minimum cell width.
	 */
	void setMinWidth(uisize_t minWidth);

	/**
	 * @brief Set where to start when displaying child widgets; on the left, or right.
	 *
	 * If `align` is ui::ALIGN_LEFT, then child widgets are rendered from left to right.
	 * If `align` is ui::ALIGN_RIGHT, then child widgets are rendered from right to left.
	 *
	 * @note ui::ALIGN_CENTER is undefined behavior and should not be used, for the sake of clarity at least.
	 */
	void setChildAlign(align_t align);

	/**
	 * @brief Get the minimum width of each cell in the row.
	 * @return The minimum cell width.
	 */
	inline uisize_t getMinWidth() const {
		return minimumWidth;
	}

	/**
	 * @brief Get where to start when displaying child widgets; on the left, or right.
	 * @return The alignment of cells in the row.
	 */
	inline align_t getChildAlign() const {
		return childAlignment;
	}

	DERIVE_EVENT_HANDLERS(Row)
};

} // namespace ui
