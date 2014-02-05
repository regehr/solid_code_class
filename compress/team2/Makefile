.PHONY: clean gdb

CC = clang
CFLAGS = -Wall -Wextra -Wno-unused -O0 -g

objects = main.o internal.o parser.o huff.o encoder.o
bin = huff

default: $(bin)

encode.o: internal.h
huff.o: huff.h internal.h
internal.o: internal.h
parser.o: parser.h internal.h
main.o: huff.h parser.h internal.h encoder.h

$(bin): $(objects)
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

gdb: $(bin)
	gdb $(bin)

clean:
	-rm $(bin) $(objects)
