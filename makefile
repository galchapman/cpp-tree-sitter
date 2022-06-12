
CC=gcc
CCC=g++
LD=ld
AR=ar

FLAGS=-Isrc/core/lib/src -Isrc/core/lib/include
CFLAGS=$(FLAGS) -std=c99
CCFLAGS=$(FLAGS) -std=c++20 

SRCS = $(wildcard src/*.cpp)
HDRS = $(wildcard src/*.hpp)
OBJS = $(patsubst src/%.cpp,src/%.o,$(SRCS))

all: libtree-sitter-cpp.a

libtree-sitter.o: $(wildcard src/core/lib/src/*.c) $(wildcard src/core/lib/src/*.h)
	$(CC) $(CFLAGS) -c src/core/lib/src/lib.c -o $@

libtree-sitter-cpp.o: $(OBJS) libtree-sitter.o
	$(LD) -r $^ -o $@

libtree-sitter-cpp.a: libtree-sitter-cpp.o
	$(AR) rcs $@ $^

src/%.o: src/%.cpp $(CCC CCFLAGS -M src/%.cpp)
	$(CCC) $(CCFLAGS) -c $< -o $@
