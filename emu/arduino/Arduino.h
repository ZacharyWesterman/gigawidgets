#pragma once

#include <chrono>
#include <cinttypes>
#include <string>

#define HIGH 1
#define LOW 0
#define PROGMEM

class String : public std::string {
public:
	String(const char *value);
	String();
	String(float value);
	String(int value);
	String(unsigned int value);
	String(size_t value);
	String(const std::basic_string<char> &value);
};

unsigned long millis();

void delay(unsigned long ms);

void digitalWrite(int pinNumber, bool pinStatus);

class serialOut {
public:
	void begin(int) const {};
	void print(const String &str) const;
	void println(const String &str) const;

	operator bool() const {
		return true;
	}
};

static serialOut Serial;
