.PHONY: default clean gdb test

CC = clang
BASE_CFLAGS = -std=c99 -Wall -Wextra -pedantic -Werror
CFLAGS = $(BASE_CFLAGS) -O3 -DNDEBUG
CFLAGS += -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function

PY = python27

objects = main.o header.o tree.o encoder.o common.o rle.o
bin = rhuff

default: $(bin)

encoder.o: encoder.h common.h
tree.o: tree.h common.h
common.o: common.h
header.o: header.h common.h
main.o: tree.h header.h common.h encoder.h
rle.o: rle.c rle.h

$(bin): $(objects)
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

gdb: $(bin)
	gdb $(bin)

clean:
	-rm -f $(bin) $(objects)
	-$(MAKE) -C test clean

test: $(bin)
	cp $(bin) test
	$(MAKE) -C test test PY=$(PY)
