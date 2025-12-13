/// @file blink.hpp
#pragma once

#include "containers/single_child_widget.hpp"

namespace ui {

/**
 * @brief A wrapper widget that causes its child to blink.
 */
class Blink : public SingleChildWidget {
private:
	/// @brief The time in milliseconds when the child widget was last rendered.
	time_t lastRender;
	/// @brief The number of milliseconds before switching from on to off and vice versa.
	time_t delay;
	/// @brief Whether the child widget is currently visible.
	bool visible;

public:
	/**
	 * @brief Constructor.
	 * @param child The child widget.
	 * @param time The number of milliseconds it takes to perform a full on/off cycle.
	 */
	Blink(Widget *child, time_t time = 1000);

	void draw() const override;
	bool update(time_t time_ms) override;

	Size size() const override;

	void drawDone() override;
};

} // namespace ui
