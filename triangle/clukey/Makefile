all:
	gcc -o triangle triangle.c -O

debug:
	gcc -Wall -Werror -g -o triangle triangle.c -O0

clean:
	rm -f triangle triangle.c.gcov triangle.gcno triangle.gcda

test:
	gcc -o triangle triangle.c -O
	./test.py