
CC=gcc
CCC=g++
LD=ld
AR=ar

BIN=bin

FLAGS=-Iinclude -Isrc/core/lib/include -fpic
DFLAGS=-g
RFLAGS=-O3
CFLAGS=$(FLAGS) -std=c99
CCFLAGS=$(FLAGS) -std=c++20 -nostdlib

SRCS = $(wildcard src/*.cpp)
HDRS = $(wildcard src/*.hpp)
OBJS = $(patsubst src/%.cpp,bin/%.o,$(SRCS))
DOBJS = $(patsubst src/%.cpp,bin/d%.o,$(SRCS))


all: $(BIN)/ libtree-sitter-cpp.a dlibtree-sitter-cpp.a

$(BIN)/libtree-sitter.o: $(wildcard src/core/lib/src/*.c) $(wildcard src/core/lib/src/*.h)
	$(CC) $(CFLAGS) $(RFLAGS) -Isrc/core/lib/src -c src/core/lib/src/lib.c -o $@

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

tree-sitter-cpp.so: $(BIN)/libtree-sitter-cpp.o
	$(CCC) -shared $^ -o $@

dtree-sitter-cpp.so: $(BIN)/dlibtree-sitter-cpp.o
	$(CCC) -shared $^ -o $@

$(BIN)/%.o: src/%.cpp $(HDRS)
	$(CCC) $(RFLAGS) $(CCFLAGS) -c $< -o $@

$(BIN)/d%.o: src/%.cpp $(HDRS)
	$(CCC) $(DFLAGS) $(CCFLAGS) -c $< -o $@

$(BIN)/:
	mkdir bin