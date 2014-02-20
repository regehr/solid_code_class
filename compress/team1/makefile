.PHONY: clean test

CC = gcc
CFLAGS = -std=c99 -Wall -Werror -O3

objects = huff.o huff_tree.o huff_io.o compress.o decode.o rle.o
bin = huff
ext = *.hurl *.huff *.dot

default: $(bin)

huff_tree.o: huff_tree.h
huff_io.o: huff_io.h

$(bin): $(objects)
	$(CC) -o rhuff $(LDFLAGS) $^ $(LDLIBS)

test:
	python test/makeTestFiles.py
	python test/runTests.py
	python test/clearTestFiles.py

release: $(objects)
	$(CC) $(CFLAGS) -D NDEBUG -o rhuff $^

clean:
	-rm -f $(bin) $(objects) $(ext)

clang: $(objects)
	clang huff.c huff_tree.c huff_io.c compress.c decode.c -fsanitize=undefined -Wall -g -O0 -o rhuff -lm
