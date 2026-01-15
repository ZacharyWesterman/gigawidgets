/// @file widget.hpp
#pragma once

#include <ctime>
#include <functional>

#include "alignment.hpp"
#include "bounds.hpp"
#include "coords.hpp"
#include "event.hpp"
#include "event_handlers.hpp"
#include "id.hpp"
#include "padding.hpp"
#include "position.hpp"
#include "size.hpp"

#ifndef ONHOLD_EVENT_DEBOUNCE
// The number of milliseconds to wait after pressing a widget before the "onhold" event gets sent.
#define ONHOLD_EVENT_DEBOUNCE 200
#endif

namespace ui {

/**
 * @brief The common interface for all UI objects.
 */
class Widget : public EventHandlers<Widget> {
	/// @brief The (optional) callback function that gets called when the touchscreen is pressed within this widget's bounds.
	std::function<void(Widget &element, const Event &event)> callbackPress;
	/// @brief The (optional) callback function that gets called when the touchscreen is held within this widget's bounds.
	std::function<void(Widget &element, const Event &event, time_t time)> callbackHold;
	/// @brief The (optional) callback function that gets called when the touchscreen is released within this widget's bounds.
	std::function<void(Widget &element, const Event &event)> callbackRelease;
	/// @brief The (optional) callback function that gets called when the touchscreen is either released or the user drags outside of this widget's bounds.
	std::function<void(Widget &element, const Event &event)> callbackBlur;

	/// @brief The parent widget, if any.
	Widget *parent;

	/// @brief If false, this widget has never been rendered. If true, it's been rendered at least once.
	bool initialRender;
	/// @brief The position of this widget relative to its parent.
	Position pos;
	/// @brief The alignment of this widget relative to its parent.
	Alignment align;
	/// @brief Whether this widget was pressed (for detecting blur events).
	bool pressed;

protected:
	/// @brief The padding that will be applied to any child widgets.
	Padding padding;
	/// @brief If true, force a redraw of the parent and any of its child widgets.
	bool redrawParent;
	/// @brief If true, force a redraw of this widget and any child widgets.
	bool redrawSelf;

public:
	id_t id;

	using EventHandlers<Widget>::onpress;
	using EventHandlers<Widget>::onrelease;
	using EventHandlers<Widget>::onblur;
	using EventHandlers<Widget>::onhold;
	using EventHandlers<Widget>::onclick;

	/**
	 * @brief The default widget constructor.
	 * @param pos The position of the widget relative to the parent.
	 * @param align The alignment of the widget relative to the parent.
	 * @param padding The padding to apply to any child widgets.
	 */
	Widget(const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	/**
	 * @brief Render the widget to the screen.
	 *
	 * This only gets called when widgets indicate that a redraw is needed of either themselves or their parents.
	 * Widgets that implement this method should take care to render as little as they can get away with,
	 * to help performance.
	 */
	virtual void draw() const = 0;

	/**
	 * @brief The default widget destructor.
	 */
	virtual ~Widget();

	/**
	 * @brief Update any internal state of the widget, and check if it needs to be re-rendered.
	 * @param time The current time in milliseconds.
	 * @return True if this widget needs to be re-rendered.
	 */
	virtual bool update(time_t time);

	/**
	 * @brief Get the size of the widget.
	 * @return The width and height of the widget in pixels.
	 * @warning This value may be based on the size of the child widget, and so should \b never refer to the size of the parent widget!
	 */
	virtual Size size() const = 0;

	/**
	 * @brief Get the rendering bounds of this widget.
	 * @return The bounds that this widget will render in.
	 * @warning This value may be based on the size of the parent widget, and so should \b never refer to the size of any child widgets!
	 */
	virtual Bounds bounds() const;

	/**
	 * @brief Set the position of this widget.
	 * @param pos The new position, relative to the parent widget.
	 */
	inline void setPosition(const Position &pos) {
		this->pos = pos;
		redrawParent = true;
	}

	/**
	 * @brief Get the position of this widget.
	 * @return The relative position of this widget on its parent.
	 */
	inline Position getPosition() const {
		return pos;
	}

	/**
	 * @brief Set the alignment of this widget.
	 * @param align The new alignment, relative to the parent widget.
	 */
	inline void setAlign(const Alignment &align) {
		this->align = align;
		redrawParent = true;
	}

	/**
	 * @brief Check if this widget has requested for the parent widget to be redrawn.
	 * @return True if this widget has requested to redraw the parent, false otherwise.
	 */
	inline bool redrawRequested() const {
		return redrawParent;
	}

	/**
	 * @brief Reset any state variables after rendering has finished.
	 */
	virtual void drawDone();

	/**
	 * @brief Set the parent widget.
	 * @param parent The parent widget.
	 */
	void setParent(Widget *parent);

	/**
	 * @brief Get the bounds of the parent widget, if any.
	 * @return The parent's bounds, or {0,0,0,0} if no parent.
	 */
	Bounds parentBounds() const;

	/**
	 * @brief Register a touchscreen event handler that triggers on press.
	 * @param callback A callback function that takes no arguments and returns nothing.
	 * @note Only one event handler for each type of event (press, hold, release, blur) is allowed per widget.
	 */
	void onpress(std::function<void(Widget &, const Event &)> callback) override;

	/**
	 * @brief Register a touchscreen event handler that triggers when the widget stops being pressed.
	 * @param callback A callback function that takes a reference to the clicked widget and returns nothing.
	 * @note Only one event handler for each type of event (press, hold, release, blur) is allowed per widget.
	 */
	void onblur(std::function<void(Widget &, const Event &)> callback) override;

	/**
	 * @brief Register a touchscreen event handler that repeatedly triggers when the widget is held for a while.
	 * @param callback A callback function that takes a reference to the clicked widget and the number of milliseconds that the widget has been held and returns nothing.
	 * @note Only one event handler for each type of event (press, hold, release, blur) is allowed per widget.
	 */
	void onhold(std::function<void(Widget &, const Event &, time_t)> callback) override;

	/**
	 * @brief Register a touchscreen event handler that triggers on release.
	 * @param callback A callback function that takes a reference to the clicked widget and returns nothing.
	 * @note Only one event handler for each type of event (press, hold, release, blur) is allowed per widget.
	 */
	void onrelease(std::function<void(Widget &, const Event &)> callback) override;

	/**
	 * @brief Manually trigger the onrelease event handler.
	 */
	void click();

	/**
	 * @brief Manually trigger the onpress event handler.
	 */
	void press();

	/**
	 * @brief Manually trigger the onblur event handler.
	 */
	void blur();

	/**
	 * @brief Manually trigger the onrelease event handler.
	 */
	void release();

	/**
	 * @brief Manually trigger the onhold event handler.
	 * @param time The number of milliseconds that the widget has been "held".
	 */
	void hold(time_t time);

	/**
	 * @brief Handle events from the touchscreen.
	 * @param event The touch event info.
	 * @return True if this widget was within the event bounds, false otherwise.
	 */
	virtual bool handleEvent(Event &event);

#ifdef DEBUG
	/**
	 * @brief Render the bounding box of this and any child widgets.
	 * @note This member function is only available in debug builds.
	 */
	virtual void drawBoundingBox(time_t time) const;
#endif

	/**
	 * @brief Get the first widget (this or any children) that has the given ID.
	 *
	 * An ID is expected to be a unique, typically non-zero value.
	 * To generate an id, you can either call `ui::id("some text")`,
	 * or (for constant strings only), `"some text"_id`.
	 *
	 * @param id The unique identifier of the widget.
	 * @return A pointer to the widget, or `nullptr` if not found.
	 */
	virtual Widget *getWidgetById(id_t id) noexcept;
};

} // namespace ui
