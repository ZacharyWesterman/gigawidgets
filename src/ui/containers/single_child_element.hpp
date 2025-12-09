#pragma once

#include "../core/widget.hpp"

namespace ui {

class SingleChildElement : public Widget {
protected:
	Widget *child;

public:
	SingleChildElement(Widget *child, const Position &pos = {0.5, 0.5}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	~SingleChildElement() override;

	Size size() const override;

	bool update(time_t time_ms) override;

	void drawDone() override;

	void setChild(Widget *const child);

	bool handleEvent(const Event &event) override;
};

} // namespace ui
