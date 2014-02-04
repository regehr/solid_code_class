all:
	clang huff.c huff_table.c -fsanitize=undefined -Wall -o huff -lm

huff: huff.c huff_table.c
	gcc -fprofile-arcs -ftest-coverage huff.c huff_table.c -o huff -lm

coverage: huff
	gcov huff

clean:
	rm -rf *.huff huff
	rm -rf 