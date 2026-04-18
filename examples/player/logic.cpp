#include "src/ui/icons/pause.hpp"
#include "src/ui/icons/play.hpp"
#include "src/ui/shaders/negative.hpp"

void mark(ui::Image &self) {
	self.setShader(ui::shader::negative);
}

void unmark(ui::Image &self) {
	self.removeShader();
}

bool playing = false;
void toggle_player(ui::Image &self) {
	playing = !playing;
	self.setRender(playing ? ui::icon::pause : ui::icon::play);
	self.removeShader();

	ui::Text *status = (ui::Text *)ui::getWidgetById("status"_id);
	if (status) {
		status->setText(playing ? "Playing" : "Paused");
	}
}
