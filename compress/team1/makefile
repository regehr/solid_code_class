.PHONY: clean test

CC = gcc
CFLAGS = -std=c99 -Wall -Werror -O3

objects = huff.o huff_tree.o huff_io.o compress.o decode.o
bin = huff

default: $(bin)

huff_tree.o: huff_tree.h
huff_io.o: huff_io.h

$(bin): $(objects)
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

test:
	python test/makeTestFiles.py
	python test/runTests.py
	python test/clearTestFiles.py

clean:
	-rm -f $(bin) $(objects)
