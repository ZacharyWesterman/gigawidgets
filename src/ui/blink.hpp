#pragma once

#include "containers/single_child_widget.hpp"

namespace ui {

class Blink : public SingleChildWidget {
private:
	unsigned long lastRender;
	bool visible;

public:
	Blink(Widget *child);

	void draw() const override;
	bool update(time_t time_ms) override;

	Size size() const override;

	void drawDone() override;
};

} // namespace ui
