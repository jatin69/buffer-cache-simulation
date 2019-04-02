CXX=gcc
CFLAGS=-std=c99 -Wall -Wextra -Wno-unused-parameter

SRC=$(shell find ./src -name "*.c")
OBJ_SRC=$(subst .c,.o,$(SRC))

all: src

src: $(OBJ_SRC) src/bufferCache.h
	$(CXX) $(CFLAGS) -c -o src/main.o src/main.c
	$(CXX) $(CFLAGS) -o bufcache $(OBJ_SRC)

%.o: %.c
	$(CXX) $(CFLAGS) -c -o $@ $<

clean: clean-src
	rm -rf $(shell find . -name "*.o")
	rm -rf ./bufcache

clean-src:
	rm -rf $(shell find ./src -name "*.o")

run:
	./bufcache

test:
	./test.sh