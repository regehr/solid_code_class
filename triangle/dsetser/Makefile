all:
	gcc -o triangle triangle.c -lm

clean:
	rm -f triangle testing/output.txt triangle.c.gcov triangle.gcno triangle.gcda

test: all
	testing/test.sh

coverage: clean
	gcc -fprofile-arcs -ftest-coverage -lm -o triangle triangle.c
	testing/test.sh
	gcov triangle
	rm -f triangle.gcno triangle.gcda
