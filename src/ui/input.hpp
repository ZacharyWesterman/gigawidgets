/// @file input.hpp
#pragma once

#include "panel.hpp"
#include "text.hpp"

namespace ui {

/**
 * @brief An interactive class of Widget for handling text input.
 *
 * A text field is constructed as a Panel widget that contains a Text widget,
 * plus a little extra rendering to show the cursor.
 */
class Input : public Panel {
	/// @brief The current cursor position.
	int cursor;
	/// @brief The last time the cursor blinked.
	time_t lastRender;
	/// @brief Whether the cursor is currently visible (used for blinking animation).
	bool showCursor;

	/// @brief Render the cursor to the screen.
	void drawCursor() const;

public:
	/**
	 * @brief Construct an Input widget with the default font.
	 * @param scale A scaling factor for the text, e.g. 2x, 3x etc.
	 * @param textColor The text color.
	 * @param backgroundColor The color of the panel behind the text.
	 * @param size The minimum size of this widget. It may expand vertically to fit the rendered text.
	 * @param pos The position of this widget relative to its parent.
	 * @param borderRadius The radius of the rounded corners of the background panel.
	 * @param align The alignment of this widget relative to its parent.
	 * @param padding The padding to apply to the text.
	 */
	Input(fontsize_t scale, color_t textColor, color_t backgroundColor, const Size &size = {0, 0}, radius_t borderRadius = 0, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	/**
	 * @brief Construct an Input widget with a specific font.
	 * @param font The font to use.
	 * @param textColor The text color.
	 * @param backgroundColor The color of the panel behind the text.
	 * @param size The minimum size of this widget. It may expand vertically to fit the rendered text.
	 * @param pos The position of this widget relative to its parent.
	 * @param borderRadius The radius of the rounded corners of the background panel.
	 * @param align The alignment of this widget relative to its parent.
	 * @param padding The padding to apply to the text.
	 */
	Input(const GFXfont *font, color_t textColor, color_t backgroundColor, const Size &size = {0, 0}, radius_t borderRadius = 0, const Position &pos = {0, 0}, const Alignment &align = {ALIGN_LEFT, ALIGN_TOP}, const Padding &padding = {0});

	/**
	 * @brief Replace the stored text with a new string.
	 * @param text The new text.
	 */
	void setText(const String &text);

	/**
	 * @brief Get the currently stored text.
	 * @return The current text.
	 */
	const String &getText() const;

	/**
	 * @brief Insert a character at the current cursor position.
	 * @param c The character to insert.
	 */
	void insert(char c);

	/**
	 * @brief Get the current cursor position.
	 * @return The cursor position.
	 */
	int getCursor() const;

	/**
	 * @brief Set the position of the cursor.
	 *
	 * If the given index is outside of the max/min cursor values, it's assigned to the end/beginning of the text, respectively.
	 *
	 * @param index The new cursor position.
	 */
	void setCursor(int index);

	/**
	 * @brief Get the nearest cursor position to a given set of screen coordinates.
	 * @param coords The coordinates to check.
	 * @return The nearest cursor position.
	 */
	int nearestCursor(const Coords &coords) const;

	void draw() const override;
	bool update(time_t time) override;

	DERIVE_EVENT_HANDLERS(Input)
};

} // namespace ui
