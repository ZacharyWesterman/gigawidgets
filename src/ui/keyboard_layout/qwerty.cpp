#include "qwerty.hpp"

namespace ui {
namespace layout {

const char *QwertyLayout::row1(bool upper, bool alt) const {
	return upper ? "QWERTYUIOP" : "qwertyuiop";
}
const char *QwertyLayout::row2(bool upper, bool alt) const {
	return upper ? "ASDFGHJKL" : "asdfghjkl";
}
const char *QwertyLayout::row3(bool upper, bool alt) const {
	return upper ? "ZXCVBNM" : "zxcvbnm";
}

} // namespace layout
} // namespace ui
