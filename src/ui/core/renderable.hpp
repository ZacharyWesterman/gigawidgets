/// @file renderable.hpp
#pragma once

#include <functional>

#include "color.hpp"
#include "coords.hpp"
#include "size.hpp"

namespace ui {

/**
 * @typedef shader_oneframe_t
 * @brief A pixel shader that's independent of the current time.
 *
 * Pixel shaders are run on a per-pixel basis and do not have access to previous data or other pixels.
 *
 * @param color The color of the current pixel, before any shader is applied.
 * @param coords The [x,y] coordinates of the pixel, relative to the renderable this shader is applied to.
 * @param size The [width,height] size of the renderable.
 */
typedef std::function<color_t(color_t color, const Coords &coords, const Size &size)> shader_oneframe_t;

/**
 * @typedef shader_animated_t
 * @brief A pixel shader that may update based on the current time.
 *
 * Pixel shaders are run on a per-pixel basis and do not have access to previous data or other pixels.
 *
 * @param color The color of the current pixel, before any shader is applied.
 * @param coords The [x,y] coordinates of the pixel, relative to the renderable this shader is applied to.
 * @param size The [width,height] size of the renderable.
 * @param time The current time in milliseconds.
 */
typedef std::function<color_t(color_t color, const Coords &coords, const Size &size, time_t time)> shader_animated_t;

/**
 * @typedef shader_t
 * @brief A pixel shader that may or may not update based on the current time.
 *
 * Pixel shaders are run on a per-pixel basis and do not have access to previous data or other pixels.
 *
 * @param color The color of the current pixel, before any shader is applied.
 * @param coords The [x,y] coordinates of the pixel, relative to the renderable this shader is applied to.
 * @param size The [width,height] size of the renderable.
 * @param time The current time in milliseconds.
 */
typedef shader_animated_t shader_t;

/**
 * @brief An abstract interface for arabitrary renderable objects.
 *
 * Renderable objects can include constructs like images, animations, etc.
 */
struct Renderable {
	/**
	 * @brief Display the renderable directly onto the screen.
	 * @param coords The coordinates to render the first pixel [0,0] of the renderable.
	 * @param shader An optional pixel shader to apply to each pixel of the renderable.
	 */
	virtual void renderAt(const Coords &coords, const shader_t &shader = 0) const = 0;

	/**
	 * @brief Get the size of the renderable.
	 * @return The size of the renderable.
	 */
	virtual Size getSize() const = 0;
};

}; // namespace ui
