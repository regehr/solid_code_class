.PHONY: clean gdb test

CC = clang
CFLAGS = -Wall -Wextra -pedantic -O2 -g

objects = main.o internal.o header.o tree.o encoder.o
bin = huff

python = python27

default: $(bin)

encoder.o: encoder.h internal.h
tree.o: tree.h internal.h
internal.o: internal.h
header.o: header.h internal.h
main.o: tree.h header.h internal.h encoder.h

$(bin): $(objects)
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

gdb: $(bin)
	gdb $(bin)

clean:
	-rm $(bin) $(objects)
	$(MAKE) -C test clean

test: $(bin)
	cp $(bin) test
	$(MAKE) -C test test python=$(python)
