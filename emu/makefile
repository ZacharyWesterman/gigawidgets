ARDUINO_INCLUDES = -I"${HOME}/Arduino/libraries/Adafruit_GFX_Library" -I"${HOME}/Arduino/libraries/Arduino_GigaDisplayTouch/src" -I"${HOME}/Arduino/libraries/Arduino_GigaDisplay_GFX/src"

SOURCES=$(shell find src -type f -iname '*.cpp')
OBJECTS=$(foreach x, $(basename $(SOURCES)), $(x).o)

ARDUINO_SOURCES=$(shell find arduino -type f -iname '*.cpp')
ARDUINO_OBJECTS=$(foreach x, $(basename $(ARDUINO_SOURCES)), $(x).o)

RAYLIB_URL = https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_linux_amd64.tar.gz
RAYLIB_TAR_FILE = $(notdir $(RAYLIB_URL))
RAYLIB_DIR = $(basename $(basename $(RAYLIB_TAR_FILE)))
RAYLIB_BIN_DIR = lib/$(RAYLIB_DIR)/lib

LIB_INCLUDES = -Isrc -Iarduino -Ilib/$(RAYLIB_DIR)/include

CC = g++
WINDOW_SCALE = 1
CFLAGS = -DEMULATE -DARDUINO=300 -DARDUINO_GIGA -DWINDOW_SCALE=$(WINDOW_SCALE) -std=c++11 $(LIB_INCLUDES) $(ARDUINO_INCLUDES) -Wno-narrowing


all: lib src ino

ino: main.o ino.o $(OBJECTS) $(ARDUINO_OBJECTS)
	$(CC) -o $@ $^ -l:libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11 -L$(RAYLIB_BIN_DIR)

main.o: main.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

arduino/%.o: arduino/%.cpp arduino/%.h
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -o $@ -c $<

src:
	rsync -a ../src .

lib: $(RAYLIB_TAR_FILE)
	mkdir -p lib
	tar xzf $< -C lib/ || rm lib -rf

$(RAYLIB_TAR_FILE):
	wget $(RAYLIB_URL)

.PHONY: clean

clean:
	rm -rf src lib ino *.o ino.cpp arduino/*.o $(RAYLIB_TAR_FILE)
