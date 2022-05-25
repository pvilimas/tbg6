COMP = g++
CFLAGS = -std=c++20 -fmodules-ts
SRC = modtest.cpp mod.cpp

all: clean build run

main: $(SRC)
	$(COMP) $(CFLAGS) $^ -o $@ $(LFLAGS)

build: main

dist: $(SRC)
	$(COMP) $(CFLAGS) $^ -o $@

run: main
	./main

clean:
	rm -f main 
	rm -rf *.dSYM
	clear