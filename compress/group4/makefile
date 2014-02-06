all:
	clang huff.c huff_io.c -o huff -Wall -fsanitize=undefined

clean:
	rm -f ./huff
	rm -f ./test.o
	rm -f *.gch

test: test.py test.o huff
	clang huff.c huff_io.c -o huff -Wall -fsanitize=undefined
	gcc test.c -o test.o
	python27 test.py huff
