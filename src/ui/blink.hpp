#pragma once

#include "containers/single_child_element.hpp"

namespace ui {

class Blink : public SingleChildElement {
private:
	unsigned long lastRender;
	bool visible;

public:
	Blink(Element *child);

	void draw() const override;
	bool update(unsigned long time_ms) override;

	Size size() const override;

	void drawDone() override;
};

} // namespace ui
