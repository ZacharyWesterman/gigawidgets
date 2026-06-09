
#include "src/ui/shaders.hpp"

#define get_widget(var, type, id) auto &var = *(ui::type *)self.getWidgetById(id);

void press_action(ui::Body &self) {
	get_widget(text, Text, "text"_id);
	get_widget(image, Image, "image"_id);

	text.setText("Evil Kitty!");
	image.setShader(ui::shader::negative);
}

void release_action(ui::Body &self) {
	get_widget(text, Text, "text"_id);
	get_widget(image, Image, "image"_id);

	text.setText("Normal Kitty :)");
	image.removeShader();
}
