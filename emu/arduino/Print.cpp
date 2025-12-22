#include "Print.h"

size_t Print::print(const String &s) {
	return write(s.c_str(), s.length());
}

size_t Print::println(const String &s) {
	size_t n = print(s);
	n += println();
	return n;
}

size_t Print::println() {
	return write("\r\n");
}
