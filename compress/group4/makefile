all:
	clang huff.c -o huff -Wall -fsanitize=undefined

clean:
	rm -f ./huff
	rm -f ./test.o

test: test.py test.o huff
	clang huff.c -o huff -Wall -fsanitize=undefined
	gcc test.c -o test.o
	python27 test.py huff
