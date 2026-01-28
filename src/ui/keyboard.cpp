#include "keyboard.hpp"
#include "column.hpp"
#include "core/display.hpp"
#include "core/units.hpp"
#include "panel.hpp"
#include "row.hpp"
#include "text.hpp"

namespace ui {

Keyboard::Keyboard(fontsize_t scale, color_t textColor, color_t buttonColor, color_t backgroundColor) : Panel(new Column(Size{ui::width(), ui::height() / 2}, {0, 0}, {ALIGN_LEFT, ALIGN_BOTTOM}, {0, 0}), backgroundColor, {0, 0}, 0, {0, 0}, {ALIGN_CENTER, ALIGN_BOTTOM}, {0, 5_px}) {
	const char *rows[] = {
		"qwertyuiop",
		"asdfghjkl",
		"zxcvbnm",
	};

	auto column = reinterpret_cast<Column *>(child);

	const int row_ct = 3;
	const int row_height = ui::height() / (2 * row_ct);
	for (int r = 0; r < row_ct; r++) {
		auto row = new ui::Row({ui::width(), row_height}, {0, 0}, {ALIGN_CENTER, ALIGN_CENTER}, {5_px, 0});
		// row->setChildAlign(ALIGN_RIGHT);

		const char *c = rows[r] - 1;
		while (*(++c)) {
			auto text = new ui::Text(String(*c), scale, textColor, {0, 0}, {ALIGN_CENTER, ALIGN_CENTER});
			auto button = new ui::Panel(text, buttonColor, {60_px, 60_px}, 5_px);
			row->push(button);

			// Bug here: I think setColor is causing the parent to re-render,
			// but it should not.
			button->onpress([](Panel &btn) { btn.setColor(COLOR_WHITE); });
			// button->onblur([buttonColor](Panel &btn) { btn.setColor(buttonColor); });
		}

		column->push(row);
	}
}

Keyboard::Keyboard(const GFXfont *font, color_t textColor, color_t buttonColor, color_t backgroundColor) : Panel(new Column(Size{ui::width(), ui::height() / 2}, {0, 0}, {ALIGN_LEFT, ALIGN_BOTTOM}, {10_px}), backgroundColor) {}

} // namespace ui
