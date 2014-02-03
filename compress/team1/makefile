C_FLAGS = -std=c99

all:
	gcc -c huff.c
	gcc -c huff_table.c
    gcc -c huff_io.c
	gcc -std=c99 huff_table.o huff_io.o huff.o -o huff

