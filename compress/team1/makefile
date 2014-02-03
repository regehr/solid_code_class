.PHONY: clean

CC = gcc
CFLAGS = -std=c99 -O2 -g

objects = huff.o huff_table.o huff_io.o
bin = huff

default: $(bin)

huff_table.o: huff_table.h
huff_io.o: huff_io.h

$(bin): $(objects)
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

clean:
	-rm -f $(bin) $(objects)