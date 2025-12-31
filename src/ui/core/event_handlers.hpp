#pragma once
#include <ctime>
#include <functional>

#include "event.hpp"

#define _DERIVE_EVENT(T, FUNC_NAME) \
	void FUNC_NAME(std::function<void(T &, const Event &)> callback) { \
		Widget::FUNC_NAME([callback](Widget &widget, const Event &event) { callback(reinterpret_cast<T &>(widget), event); }); \
	} \
	void FUNC_NAME(std::function<void(T &)> callback) { \
		Widget::FUNC_NAME([callback](Widget &widget, const Event &) { callback(reinterpret_cast<T &>(widget)); }); \
	}

#define _DERIVE_EVENT_TIME(T, FUNC_NAME) \
	void FUNC_NAME(std::function<void(T &, const Event &, time_t)> callback) { \
		Widget::FUNC_NAME([callback](Widget &widget, const Event &event, time_t time) { callback(reinterpret_cast<T &>(widget), event, time); }); \
	} \
	void FUNC_NAME(std::function<void(T &, time_t)> callback) { \
		Widget::FUNC_NAME([callback](Widget &widget, const Event &, time_t time) { callback(reinterpret_cast<T &>(widget), time); }); \
	} \
	void FUNC_NAME(std::function<void(T &)> callback) { \
		Widget::FUNC_NAME([callback](Widget &widget, const Event &, time_t) { callback(reinterpret_cast<T &>(widget)); }); \
	}

#define DERIVE_EVENT_HANDLERS(T) \
	_DERIVE_EVENT(T, onpress) \
	_DERIVE_EVENT(T, onrelease) \
	_DERIVE_EVENT(T, onblur) \
	_DERIVE_EVENT(T, onclick) \
	_DERIVE_EVENT_TIME(T, onhold)

namespace ui {

template <class T>
class CoreEventHandlers {
public:
	/**
	 * @brief Register a touchscreen event handler that triggers on press.
	 * @param callback A callback function that is called when this widget receives a "press" event.
	 * @note Only one event handler for each type of event (press, hold, release, blur) is allowed per widget.
	 */
	virtual void onpress(std::function<void(T &, const Event &)> callback) = 0;

	/**
	 * @brief Register a touchscreen event handler that triggers when the widget stops being pressed.
	 * @param callback A callback function that is called when this widget receives a "release" event.
	 * @note Only one event handler for each type of event (press, hold, release, blur) is allowed per widget.
	 */
	virtual void onrelease(std::function<void(T &, const Event &)> callback) = 0;

	/**
	 * @brief Register a touchscreen event handler that triggers when the widget stops being pressed.
	 * @param callback A callback function that is called when a widget stops being pressed after previously receiving a "press" event.
	 * @note Only one event handler for each type of event (press, hold, release, blur) is allowed per widget.
	 */
	virtual void onblur(std::function<void(T &, const Event &)> callback) = 0;

	/**
	 * @brief Register a touchscreen event handler that repeatedly triggers when the widget is held for a while.
	 * @param callback A callback function that is called when this widget has been continuously pressed for a while.
	 * @note Only one event handler for each type of event (press, hold, release, blur) is allowed per widget.
	 */
	virtual void onhold(std::function<void(T &, const Event &, time_t)> callback) = 0;

	/**
	 * @brief Register a touchscreen event handler that triggers on release.
	 *
	 * This is identical to the onrelease() function.
	 *
	 * @param callback A callback function that is called when this widget receives a "release" event.
	 * @note Only one event handler for each type of event (press, hold, release, blur) is allowed per widget.
	 */
	inline void onclick(std::function<void(T &, const Event &)> callback) {
		onrelease(callback);
	}
};

template <class T>
class EventHandlers : public CoreEventHandlers<T> {
public:
	using CoreEventHandlers<T>::onpress;
	using CoreEventHandlers<T>::onrelease;
	using CoreEventHandlers<T>::onblur;
	using CoreEventHandlers<T>::onhold;
	using CoreEventHandlers<T>::onclick;

	inline void onpress(std::function<void(T &)> callback) {
		onpress([callback](T &widget, const Event &) { callback(widget); });
	}

	inline void onpress(std::function<void(const Event &)> callback) {
		onpress([callback](T &, const Event &event) { callback(event); });
	}

	inline void onpress(std::function<void()> callback) {
		onpress([callback](T &, const Event &) { callback(); });
	}

	inline void onrelease(std::function<void(T &)> callback) {
		onrelease([callback](T &widget, const Event &) { callback(widget); });
	}

	inline void onrelease(std::function<void(const Event &)> callback) {
		onrelease([callback](T &, const Event &event) { callback(event); });
	}

	inline void onrelease(std::function<void()> callback) {
		onrelease([callback](T &, const Event &) { callback(); });
	}

	inline void onblur(std::function<void(T &)> callback) {
		onblur([callback](T &widget, const Event &) { callback(widget); });
	}

	inline void onblur(std::function<void(const Event &)> callback) {
		onblur([callback](T &, const Event &event) { callback(event); });
	}

	inline void onblur(std::function<void()> callback) {
		onblur([callback](T &, const Event &) { callback(); });
	}

	inline void onhold(std::function<void(T &, time_t)> callback) {
		onhold([callback](T &widget, const Event &, time_t time) { callback(widget, time); });
	}

	inline void onhold(std::function<void(const Event &, time_t)> callback) {
		onhold([callback](T &, const Event &event, time_t time) { callback(event, time); });
	}

	inline void onhold(std::function<void(time_t)> callback) {
		onhold([callback](T &, const Event &, time_t time) { callback(time); });
	}

	inline void onhold(std::function<void(T &)> callback) {
		onhold([callback](T &widget, const Event &, time_t) { callback(widget); });
	}

	inline void onhold(std::function<void(const Event &)> callback) {
		onhold([callback](T &, const Event &event, time_t) { callback(event); });
	}

	inline void onhold(std::function<void()> callback) {
		onhold([callback](T &, const Event &, time_t) { callback(); });
	}

	inline void onclick(std::function<void(T &)> callback) {
		onclick([callback](T &widget, const Event &) { callback(widget); });
	}

	inline void onclick(std::function<void(const Event &)> callback) {
		onclick([callback](T &, const Event &event) { callback(event); });
	}

	inline void onclick(std::function<void()> callback) {
		onclick([callback](T &, const Event &) { callback(); });
	}
};

template <class Derived>
class DeriveEventHandlers : public EventHandlers<Derived> {
public:
	using EventHandlers<Derived>::onpress;
	using EventHandlers<Derived>::onrelease;
	using EventHandlers<Derived>::onblur;
	using EventHandlers<Derived>::onhold;
	using EventHandlers<Derived>::onclick;
};

} // namespace ui
