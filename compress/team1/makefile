all: huff
	gcc -std=c99 huff_table.o huff_io.o huff.o -o huff

huff: table io huff.o
	gcc -c huff.c

table: huff_table.o
	gcc -c huff_table.c
    
io: huff_io.o
	gcc -c huff_io.c

clean:
	rm -f *.o huff