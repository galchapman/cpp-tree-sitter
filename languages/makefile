CC=gcc
CCC=g++
LD=ld
PYTHON=python

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.cc
	$(CCC) $(CCFLAGS) -c $^ -o $@

%-lang:
	$(PYTHON) generate_language.py --install $(patsubst %-lang,%,$@)

languages.so: $(wildcard bin/*.o)
	$(CCC) -shared $^ -o $@

languages.o: $(wildcard bin/*.o)
	$(LD) -r $^ -o $@