#include "padding.hpp"

namespace ui {

Padding::Padding(uisize_t size) : left(size), top(size), right(size), bottom(size) {}
Padding::Padding(uisize_t left_right, uisize_t top_bottom) : left(left_right), top(top_bottom), right(left_right), bottom(top_bottom) {}
Padding::Padding(uisize_t left, uisize_t top, uisize_t right, uisize_t bottom) : left(left), top(top), right(right), bottom(bottom) {}

} // namespace ui
