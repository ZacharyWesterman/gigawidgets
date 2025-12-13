/// @file image.hpp
#pragma once

#include "core/renderable.hpp"
#include "core/widget.hpp"

namespace ui {

/**
 * @brief Display an arbitrary (non-animated) renderable to the screen with an optional shader.
 */
class Image : public Widget {
	const Renderable *const renderable;
	shader_t shader;
	/// @brief True if the shader requires re-rendering every frame, false otherwise.
	bool renderEveryFrame;

public:
	/**
	 * @brief Construct an image from some renderable data.
	 * @param renderable The data that will be rendered to the screen.
	 * @param pos The position of this image relative to its parent.
	 * @param align The alignment of this image relative to its parent.
	 */
	Image(const Renderable *const renderable, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP});

	void draw() const override;
	Size size() const override;
	bool update(time_t time_ms) override;

	/**
	 * @brief Set the image shader to a new one that requires re-rendering every frame.
	 * @param shader The new shader.
	 */
	void setShader(const shader_animated_t &shader);

	/**
	 * @brief Set the image shader to one that only requires rendering once.
	 * @param shader The new shader.
	 */
	void setShader(const shader_oneframe_t &shader);

	/**
	 * @brief Remove the shader from the image, if any exists.
	 */
	void removeShader();
};

} // namespace ui
