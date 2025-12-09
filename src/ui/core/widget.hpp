#pragma once

#include <functional>

#include "alignment.hpp"
#include "bounds.hpp"
#include "coords.hpp"
#include "event.hpp"
#include "padding.hpp"
#include "position.hpp"
#include "size.hpp"

#define ONHOLD_EVENT_DEBOUNCE 200 // milliseconds to wait before the "onhold" event gets sent

namespace ui {

class Widget {
private:
	std::function<void(Widget &element)> callbackPress;
	std::function<void(Widget &element, unsigned long)> callbackHold;
	std::function<void(Widget &element)> callbackRelease;
	std::function<void(Widget &element)> callbackBlur;

	Widget *parent;
	bool initialRender;
	Position pos;
	Alignment align;
	bool pressed;

protected:
	Padding padding;
	bool redrawParent;
	bool redrawSelf;

public:
	Widget(const Position &pos = {0.5, 0.5}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	virtual void draw() const = 0;

	virtual ~Widget();

	virtual bool update(time_t time);

	virtual Size size() const = 0;
	virtual Bounds bounds() const;

	inline void setPos(const Position &pos) {
		this->pos = pos;
		redrawParent = true;
	}

	inline void setAlign(const Alignment &align) {
		this->align = align;
		redrawParent = true;
	}

	inline bool redrawRequested() const {
		return redrawParent;
	}

	virtual void drawDone();

	void setParent(Widget *parent);

	Bounds parentBounds() const;

	void onclick(std::function<void(Widget &)> callback);
	void onclick(std::function<void()> callback);

	void onpress(std::function<void(Widget &)> callback);
	void onpress(std::function<void()> callback);

	void onblur(std::function<void(Widget &)> callback);
	void onblur(std::function<void()> callback);

	void onhold(std::function<void(Widget &, unsigned long)> callback);
	void onhold(std::function<void(unsigned long)> callback);

	void onrelease(std::function<void(Widget &)> callback);
	void onrelease(std::function<void()> callback);

	void click();
	void press();
	void blur();
	void release();
	void hold(time_t time);

	virtual bool handleEvent(const Event &event);
};

} // namespace ui
