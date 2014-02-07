.PHONY: clean test

CC = gcc
CFLAGS = -std=c99 -Wall -O2 -g -pg

objects = huff.o huff_tree.o huff_io.o compress.o decode.o
bin = huff

default: $(bin)

huff_table.o: huff_tree.h
huff_io.o: huff_io.h

$(bin): $(objects)
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

test:
	python test/makeTestFiles.py
	python test/runTests.py
	python test/clearTestFiles.py

clean:
	-rm -f $(bin) $(objects)
