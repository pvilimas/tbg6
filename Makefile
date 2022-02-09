COMP = g++
CFLAGS = -std=c++20 -Wall -Wextra -pedantic -O2
LFLAGS = -lm -Iinclude -lraylib
SRC = main.cpp game.cpp command.cpp item.cpp room.cpp graphics.cpp utils.cpp

all: clean build run

main: $(SRC)
	$(COMP) $(CFLAGS) $^ -o build/$@ $(LFLAGS)

build: main #dist

dist: $(SRC)
	$(COMP) $(CFLAGS) $^ -o dist/mac/$@
	mv -f dist/mac/dist dist/mac/game

run: main
	./build/main

clean:
	rm -f build/main
	rm -rf build/*.dSYM
	clear