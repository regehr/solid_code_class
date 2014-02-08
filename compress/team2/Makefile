.PHONY: clean gdb test

CC = clang
CFLAGS = -std=c99 -Wall -Wextra -pedantic -Werror -O3

PY = python27

objects = main.o header.o tree.o encoder.o common.o 
bin = huff

default: $(bin)

encoder.o: encoder.h common.h
tree.o: tree.h common.h
common.o: common.h
header.o: header.h common.h
main.o: tree.h header.h common.h encoder.h

$(bin): $(objects)
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

gdb: $(bin)
	gdb $(bin)

clean:
	-rm -f $(bin) $(objects)
	-$(MAKE) -C test clean

test: $(bin)
	cp $(bin) test
	$(MAKE) -C test all PY=$(PY)
