/// @file column.hpp
#pragma once

#include "collection.hpp"

namespace ui {

/**
 * @brief A container widget that vertically organizes its children into a structured column.
 */
class Column : public Collection {
	/// @brief The minimum width of each cell in the row.
	uisize_t minimumHeight = 0;
	/// @brief Where to start when displaying child widgets; on the top, or bottom.
	align_t childAlignment = ALIGN_TOP;

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
	 * @brief Set the minimum height of each cell in the column.
	 * @param minHeight The minimum cell height.
	 */
	void setMinHeight(uisize_t minHeight);

	/**
	 * @brief Set where to start when displaying child widgets; on the top, or bottom.
	 *
	 * If `align` is ui::ALIGN_TOP, then child widgets are rendered from top to bottom.
	 * If `align` is ui::ALIGN_BOTTOM, then child widgets are rendered from bottom to top.
	 *
	 * @note ui::ALIGN_CENTER is undefined behavior and should not be used, for the sake of clarity at least.
	 */
	void setChildAlign(align_t align);

	/**
	 * @brief Get the minimum height of each cell in the column.
	 * @return The minimum cell height.
	 */
	inline uisize_t getMinHeight() const {
		return minimumHeight;
	}

	/**
	 * @brief Get where to start when displaying child widgets; on the top, or bottom.
	 * @return The alignment of cells in the column.
	 */
	inline align_t getChildAlign() const {
		return childAlignment;
	}

	DERIVE_EVENT_HANDLERS(Column)
};

} // namespace ui
