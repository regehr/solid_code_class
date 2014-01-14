all:
	gcc triangle.c -o triangle -fprofile-arcs -ftest-coverage

clean:
	rm triangle triangle.c.gcov triangle.gcda triangle.gcno

test:
	./triangle_test.sh
	gcov -b triangle
	