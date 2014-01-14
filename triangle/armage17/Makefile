all:
	gcc triangle.c -o triangle -lm -fprofile-arcs -ftest-coverage

clean:
	rm triangle
	rm *.gcno
	rm *.gcda
	rm *.gcov
	rm -f *~

test:
	python27 tests.py
	gcov triangle.c