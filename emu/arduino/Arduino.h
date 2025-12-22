#pragma once

#include <chrono>
#include <string>

#define HIGH 1
#define LOW 0
#define PROGMEM

typedef std::string String;

unsigned long millis();

void delay(unsigned long ms);

void digitalWrite(int pinNumber, bool pinStatus);

class serialOut {
public:
	void print(const String &str) const;
	void println(const String &str) const;
};

static serialOut Serial;
