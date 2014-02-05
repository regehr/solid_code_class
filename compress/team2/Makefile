.PHONY: clean gdb

CC = clang
CFLAGS = -Wall -Wextra -pedantic -O0 -g

objects = main.o internal.o header.o huff.o encoder.o
bin = huff

default: $(bin)

encoder.o: encoder.h internal.h
huff.o: huff.h internal.h
internal.o: internal.h
header.o: header.h internal.h
main.o: huff.h header.h internal.h encoder.h

$(bin): $(objects)
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

gdb: $(bin)
	gdb $(bin)

clean:
	-rm $(bin) $(objects)
