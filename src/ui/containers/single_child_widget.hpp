/// @file single_child_widget.hpp
#pragma once

#include "../core/widget.hpp"

namespace ui {

/**
 * @brief The common interface for a widget that contains a single child.
 */
class SingleChildWidget : public Widget {
protected:
	/// @brief The child widget.
	Widget *child;

public:
	/**
	 * @brief Constructor.
	 * @param child The child widget.
	 * @param pos The position of this widget relative to its parent.
	 * @param align The alignment of this widget relative to its parent.
	 * @param padding The padding to apply to the child widget.
	 */
	SingleChildWidget(Widget *child, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	/**
	 * @brief Destructor.
	 *
	 * This automatically handles destroying the child widget when this widget is destroyed.
	 */
	~SingleChildWidget() override;

	Size size() const override;
	bool update(time_t time_ms) override;
	void drawDone() override;

	/**
	 * @brief Set the child widget.
	 * @param child The new child widget.
	 *
	 * If this widget already has a child, that previous child widget is destroyed.
	 */
	void setChild(Widget *const child);

	bool handleEvent(const Event &event) override;

#ifdef DEBUG
	virtual void drawBoundingBox(time_t time) const override;
#endif
};

} // namespace ui
