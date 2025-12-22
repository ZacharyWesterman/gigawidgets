#include "Arduino.h"

#include <chrono>
#include <iostream>
#include <thread>

unsigned long millis() {
	static auto begin = std::chrono::system_clock::now();
	auto elapsed = std::chrono::system_clock::now() - begin;

	return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
}

void delay(unsigned long ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void digitalWrite(int pinNumber, bool pinStatus) {}

void serialOut::print(const String &str) const {
	std::cout << str << std::flush;
}

void serialOut::println(const String &str) const {
	std::cout << str << std::endl;
}
