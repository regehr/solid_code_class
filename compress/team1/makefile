.PHONY: clean test

CC = gcc
CFLAGS = -std=c99 -O2 -g

objects = huff.o huff_table.o huff_io.o
bin = huff

default: $(bin)

huff_table.o: huff_table.h
huff_io.o: huff_io.h

$(bin): $(objects)
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

test:
	python test/makeTestFiles.py
	python test/runTests.py
	python test/clearTestFiles.py

clean:
	-rm -f $(bin) $(objects)