#pragma once

#include "../core/element.hpp"

namespace ui {

class SingleChildElement : public Element {
protected:
	Element *child;

public:
	SingleChildElement(Element *child, const Position &pos = {0.5, 0.5}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	~SingleChildElement() override;

	Size size() const override;

	bool update(unsigned long time_ms) override;

	void drawDone() override;

	void setChild(Element *const child);

	bool handleEvent(const Event &event) override;
};

} // namespace ui
