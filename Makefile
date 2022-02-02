CC = g++
CFLAGS = -std=c++20 -Wall -Wextra -pedantic -O2 #-fsanitize=address -fsanitize=undefined -g
LFLAGS = -lm -Iinclude -lraylib
SRC = main.cpp

all: clean build run

main: $(SRC)
	$(CC) $(CFLAGS) $^ -o build/$@ $(LFLAGS)

build: main #dist

dist: $(SRC)
	$(CC) $(CFLAGS) $^ -o dist/mac/$@
	mv -f dist/mac/dist dist/mac/game

run: main
	./build/main

clean:
	rm -f build/main
	rm -rf build/*.dSYM
	clear