/// @file multi_child_widget.hpp
#pragma once

#include <vector>

#include "../core/widget.hpp"

namespace ui {

/**
 * @brief The common interface for a widget that contains multiple children.
 */
class MultiChildWidget : public Widget {
protected:
	/// @brief The child widgets.
	std::vector<Widget *> children;

public:
	/**
	 * @brief Constructor.
	 * @param pos The position of this widget relative to its parent.
	 * @param align The alignment of this widget relative to its parent.
	 * @param padding The padding to apply to the child widget.
	 */
	MultiChildWidget(const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	/**
	 * @brief Destructor.
	 *
	 * This automatically handles destroying the child widget when this widget is destroyed.
	 */
	~MultiChildWidget() override;

	bool update(time_t time_ms) override;
	void drawDone() override;
	void draw() const override;

	/**
	 * @brief Append a child widget.
	 * @param child The new child widget.
	 */
	virtual void addChild(Widget *const child);

	bool handleEvent(const Event &event) override;
};

} // namespace ui
