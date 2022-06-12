CC=gcc

FLAGS=-g -I../src/core/lib/include
CFLAGS=$(FLAGS) --std=c99

%_parser.c: generate_language.py
	python generate_language.py $(patsubst %-lang,%,$@)

%-lang.o: %_parser.c
	$(CC) $(CFLAGS) -c $^ -o $@