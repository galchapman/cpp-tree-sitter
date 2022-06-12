CC=gcc
CCC=g++
LD=ld
PYTHON=python

FLAGS=-I../src/core/lib/include
CFLAGS=$(FLAGS) --std=c99
CCFLAGS=$(FLAGS) --std=c++20

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.cc
	$(CCC) $(CCFLAGS) -c $^ -o $@

%-lang.o:
	$(PYTHON) generate_language.py --install $(patsubst %-lang.o,%,$@)
	make $(patsubst %.cc,$(patsubst %-lang.o,%,$@)_%.o,$(patsubst %.c,$(patsubst %-lang.o,%,$@)_%.o,$(shell $(PYTHON) generate_language.py $(patsubst %-lang.o,%,$@))))
	$(LD) -r $(patsubst %.cc,$(patsubst %-lang.o,%,$@)_%.o,$(patsubst %.c,$(patsubst %-lang.o,%,$@)_%.o,$(shell $(PYTHON) generate_language.py $(patsubst %-lang.o,%,$@)))) -o $@