
CC=gcc
CCC=g++
LD=ld
AR=ar

BIN=bin

FLAGS=-Iinclude -Isrc/core/lib/include
DFLAGS=-g
CFLAGS=$(FLAGS) -std=c99
CCFLAGS=$(FLAGS) -std=c++20

SRCS = $(wildcard src/*.cpp)
HDRS = $(wildcard src/*.hpp)
OBJS = $(patsubst src/%.cpp,bin/%.o,$(SRCS))
DOBJS = $(patsubst src/%.cpp,bin/d%.o,$(SRCS))


all: $(BIN)/ libtree-sitter-cpp.a dlibtree-sitter-cpp.a

$(BIN)/libtree-sitter.o: $(wildcard src/core/lib/src/*.c) $(wildcard src/core/lib/src/*.h)
	$(CC) $(CFLAGS) -Isrc/core/lib/src -c src/core/lib/src/lib.c -o $@

$(BIN)/dlibtree-sitter.o: $(wildcard src/core/lib/src/*.c) $(wildcard src/core/lib/src/*.h)
	$(CC) $(CFLAGS) $(DFLAGS) -Isrc/core/lib/src -c src/core/lib/src/lib.c -o $@

$(BIN)/libtree-sitter-cpp.o: $(OBJS) $(BIN)/libtree-sitter.o
	$(LD) -r $^ -o $@

$(BIN)/dlibtree-sitter-cpp.o: $(DOBJS) $(BIN)/dlibtree-sitter.o
	$(LD) -r $^ -o $@

libtree-sitter-cpp.a: $(BIN)/libtree-sitter-cpp.o
	$(AR) rcs $@ $^

dlibtree-sitter-cpp.a: $(BIN)/dlibtree-sitter-cpp.o
	$(AR) rcs $@ $^

$(BIN)/%.o: src/%.cpp $(HDRS)
	$(CCC) $(CCFLAGS) -c $< -o $@

$(BIN)/d%.o: src/%.cpp $(HDRS)
	$(CCC) $(DFLAGS) $(CCFLAGS) -c $< -o $@

$(BIN)/:
	mkdir bin