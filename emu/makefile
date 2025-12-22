ARDUINO_INCLUDES = -I"${HOME}/Arduino/libraries/Adafruit_GFX_Library" -I"${HOME}/Arduino/libraries/Arduino_GigaDisplayTouch/src" -I"${HOME}/Arduino/libraries/Arduino_GigaDisplay_GFX/src"

CC = g++
CFLAGS = -DEMULATE -DARDUINO=300 -DARDUINO_GIGA -std=c++11 -Iarduino $(ARDUINO_INCLUDES) -Wno-narrowing
INO_FILE = xx.ino

SOURCES=$(shell find src -type f -iname '*.cpp')
OBJECTS=$(foreach x, $(basename $(SOURCES)), $(x).o)

ARDUINO_SOURCES=$(shell find arduino -type f -iname '*.cpp')
ARDUINO_OBJECTS=$(foreach x, $(basename $(ARDUINO_SOURCES)), $(x).o)

all: src ino

ino: main.o ino.o $(OBJECTS) $(ARDUINO_OBJECTS)
	$(CC) -o $@ $^

main.o: main.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

arduino/%.o: arduino/%.cpp arduino/%.h
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -o $@ -c $<

src:
	rsync -a ../src .

.PHONY: clean

clean:
	rm -rf src main.o ino.o ino.cpp $(ARDUINO_OBJECTS)
