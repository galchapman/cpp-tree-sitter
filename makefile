
CC=gcc
CCC=g++
LD=ld
AR=ar

BIN=bin

FLAGS=-Iinclude -Isrc/core/lib/include
CFLAGS=$(FLAGS) -std=c99
CCFLAGS=$(FLAGS) -std=c++20 

SRCS = $(wildcard src/*.cpp)
HDRS = $(wildcard src/*.hpp)
OBJS = $(patsubst src/%.cpp,bin/%.o,$(SRCS))


all: $(BIN)/ libtree-sitter-cpp.a

$(BIN)/libtree-sitter.o: $(wildcard src/core/lib/src/*.c) $(wildcard src/core/lib/src/*.h)
	$(CC) $(CFLAGS) -Isrc/core/lib/src -c src/core/lib/src/lib.c -o $@

$(BIN)/libtree-sitter-cpp.o: $(OBJS) $(BIN)/libtree-sitter.o
	$(LD) -r $^ -o $@

libtree-sitter-cpp.a: $(BIN)/libtree-sitter-cpp.o
	$(AR) rcs $@ $^

$(BIN)/%.o: src/%.cpp $(HDRS)
	$(CCC) $(CCFLAGS) -c $< -o $@

$(BIN)/:
	mkdir bin