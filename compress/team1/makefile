.PHONY: clean test

CC = gcc
CFLAGS = -std=c99 -Wall -Werror -O3

objects = huff.o huff_tree.o huff_io.o compress.o decode.o rle.o
bin = rhuff
ext = *.hurl *.huff *.dot

default: $(bin)

huff_tree.o: huff_tree.h
huff_io.o: huff_io.h

$(bin): $(objects)
	$(CC) -o $(bin) $(LDFLAGS) $^ $(LDLIBS)

val: $(bin) test.txt
	valgrind --leak-check=yes ./$(bin) -c test.txt

test:
	python test/makeTestFiles.py
	python test/runTests.py
	python test/clearTestFiles.py

rle_test: rle.c test_rle.c
	gcc -c -o rle.o rle.c
	gcc -c -o test_rle.o test_rle.c
	gcc -o rle rle.o test_rle.o

release: $(objects)
	$(CC) $(CFLAGS) -D NDEBUG -o rhuff $^

clean:
	-rm -f $(bin) $(objects) $(ext) rle test_rle.o

clang: $(objects)
	clang huff.c huff_tree.c huff_io.c compress.c decode.c -fsanitize=undefined -Wall -g -O0 -o rhuff -lm
