#pragma once

#include "core/widget.hpp"

namespace ui {

class DemoWidget : public Widget {
public:
	bool update(time_t time) override; // optional
	void draw() const override;				 // MUST override
	Size size() const override;				 // MUST override
};

} // namespace ui
