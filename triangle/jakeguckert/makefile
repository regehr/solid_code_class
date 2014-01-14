all:
	gcc triangle.c -o triangle -lm -fprofile-arcs -ftest-coverage

clean:
	rm -f triangle triangle.c.gcov triangle.gcda triangle.gcno

test:
	./triangle_test.sh
	gcov -b triangle
	