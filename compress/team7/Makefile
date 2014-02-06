all:
	clang huff.c huff_table.c -fsanitize=undefined -Wall -o huff -lm

huff: huff.c huff_table.c
	gcc -fprofile-arcs -ftest-coverage huff.c huff_table.c -o huff -lm

coverage: huff test.txt
	./huff -t test.txt
	gcov huff

val: huff test.txt
	valgrind --leak-check=yes ./huff -t test.txt

clean:
	rm -rf *.huff huff
	rm -rf *.gcov *.gcno *.gcda