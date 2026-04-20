#include "src/ui.hpp"
#include "src/ui/icons/play.hpp"
#include "src/ui/icons/image.hpp"
#include <Fonts/FreeSerif18pt7b.h>
#include <Fonts/FreeSerifBold24pt7b.h>
#include "src/ui/icons/backward.hpp"
#include "src/ui/icons/forward_fast.hpp"
#include "src/ui/icons/forward.hpp"
#include "src/ui/icons/backward_fast.hpp"

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
	// self.removeShader();

	ui::Text *status = (ui::Text *)ui::getWidgetById("status"_id);
	if (status) {
		status->setText(playing ? "Playing" : "Paused");
	}
}

ui::Widget* player() {
  ui::setRotation(ui::ROT_90_DEG);
  auto _5 = new ui::Image(ui::icon::image, {0.0, 0.0}, {ui::ALIGN_CENTER, ui::ALIGN_CENTER});
  auto _4 = new ui::Panel(_5,0x4510,{50_vw, 75_vh},0_px,{0.0, 0.0},{ui::ALIGN_LEFT, ui::ALIGN_TOP},0_px);
  auto _7 = new ui::Text("Song Name", FreeSerifBold24pt7b, ui::COLOR_WHITE, {0.0, 0.0}, {ui::ALIGN_LEFT, ui::ALIGN_TOP}, 0_px);
  auto _8 = new ui::Text("Album Name", FreeSerif18pt7b, ui::COLOR_WHITE, {0.0, 0.0}, {ui::ALIGN_LEFT, ui::ALIGN_TOP}, 0_px);
  auto _9 = new ui::Text("Artist Name", FreeSerif18pt7b, ui::COLOR_WHITE, {0.0, 0.0}, {ui::ALIGN_LEFT, ui::ALIGN_TOP}, 0_px);
  auto _10 = new ui::Text("1/20", FreeSerif18pt7b, ui::COLOR_WHITE, {0.0, 0.0}, {ui::ALIGN_LEFT, ui::ALIGN_TOP}, 0_px);
  auto _12 = new ui::Text("Paused", FreeSerif18pt7b, ui::COLOR_GRAY, {0.0, 0.0}, {ui::ALIGN_LEFT, ui::ALIGN_TOP}, 0_px);
  _12->id = "status"_id;
  auto _11 = new ui::Panel(_12,0x2288,{30_vw, 10_vh},0_px,{0.0, 0.0},{ui::ALIGN_LEFT, ui::ALIGN_TOP},0_px);
  auto _6 = new ui::Column({50_vw, 50_vh},{0.0, 0.0},{ui::ALIGN_RIGHT, ui::ALIGN_CENTER},{0.2_cm, 0_px});
  _6->push(_7);
  _6->push(_8);
  _6->push(_9);
  _6->push(_10);
  _6->push(_11);
  auto _3 = new ui::Row({100_vw, 75_vh},{0.0, 0.0},{ui::ALIGN_LEFT, ui::ALIGN_TOP},0_px);
  _3->push(_4);
  _3->push(_6);
  auto _15 = new ui::Image(ui::icon::backward_fast, {0.0, 0.0}, {ui::ALIGN_LEFT, ui::ALIGN_TOP});
  _15->onblur(unmark);
  _15->onpress(mark);
  auto _16 = new ui::Image(ui::icon::backward, {0.0, 0.0}, {ui::ALIGN_LEFT, ui::ALIGN_TOP});
  _16->onblur(unmark);
  _16->onpress(mark);
  auto _17 = new ui::Image(ui::icon::play, {0.0, 0.0}, {ui::ALIGN_LEFT, ui::ALIGN_TOP});
  _17->onblur(unmark);
  _17->onpress(mark);
  _17->onrelease(toggle_player);
  auto _18 = new ui::Image(ui::icon::forward, {0.0, 0.0}, {ui::ALIGN_LEFT, ui::ALIGN_TOP});
  _18->onblur(unmark);
  _18->onpress(mark);
  auto _19 = new ui::Image(ui::icon::forward_fast, {0.0, 0.0}, {ui::ALIGN_LEFT, ui::ALIGN_TOP});
  _19->onblur(unmark);
  _19->onpress(mark);
  auto _14 = new ui::Row({69_vw, 25_vh},{0.0, 0.0},{ui::ALIGN_CENTER, ui::ALIGN_CENTER},5_px);
  _14->push(_15);
  _14->push(_16);
  _14->push(_17);
  _14->push(_18);
  _14->push(_19);
  auto _13 = new ui::Panel(_14,0x340c,{100_vw, 25_vh},0_px,{0.0, 0.0},{ui::ALIGN_LEFT, ui::ALIGN_TOP},0_px);
  auto _2 = new ui::Column({100_vw, 100_vh},{0.0, 0.0},{ui::ALIGN_LEFT, ui::ALIGN_TOP},0_px);
  _2->push(_3);
  _2->push(_13);
  auto _1 = new ui::Body(_2,0x2288,0_px);
  return _1;
}
void setup() {
    ui::setRoot(player());
}
void loop() {
    ui::render();
}
