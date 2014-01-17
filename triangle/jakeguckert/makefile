all:
	gcc triangle.c -o triangle -lm -fprofile-arcs -ftest-coverage

clean:
	rm -f triangle triangle.c.gcov triangle.gcda triangle.gcno

test:
	python triangle_test.py
	gcov -b triangle
	