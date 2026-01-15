#include "Arduino.h"

#include <chrono>
#include <iostream>
#include <thread>

String::String(const char *value) : std::string(value) {}
String::String() : std::string() {}
String::String(int value) : std::string(std::to_string(value)) {}
String::String(unsigned int value) : std::string(std::to_string(value)) {}
String::String(long value) : std::string(std::to_string(value)) {}
String::String(unsigned long value) : std::string(std::to_string(value)) {}
String::String(float value) : std::string(std::to_string(value)) {}
String::String(const std::basic_string<char> &value) : std::string(value) {}

String String::substring(unsigned int beginIndex, unsigned int endIndex) const {
	return substr(beginIndex, endIndex);
}

unsigned long millis() {
	static auto begin = std::chrono::system_clock::now();
	auto elapsed = std::chrono::system_clock::now() - begin;

	return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
}

void delay(unsigned long ms) {
	// std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void digitalWrite(int pinNumber, bool pinStatus) {}

void serialOut::print(const String &str) const {
	std::cout << str << std::flush;
}

void serialOut::println(const String &str) const {
	std::cout << str << std::endl;
}
