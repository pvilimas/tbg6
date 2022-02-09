COMP = g++
CFLAGS = -std=c++20 -Wall -Wextra -pedantic -O2
LFLAGS = -lm -Iinclude -lraylib
SRC = main.cpp game.cpp command.cpp item.cpp room.cpp graphics.cpp utils.cpp
PLATFORM = mac


all: clean build run

main: $(SRC)
	$(COMP) $(CFLAGS) $^ -o build/$@ $(LFLAGS)

build: main #dist

dist: clean build
	@cp -rf ./assets dist/$(PLATFORM)/assets
	@cp build/main dist/$(PLATFORM)/textbasedgame
	@echo "Build completed for $(PLATFORM)"

run: main
	./build/main

clean:
	rm -f build/main
	rm -rf build/*.dSYM
	clear