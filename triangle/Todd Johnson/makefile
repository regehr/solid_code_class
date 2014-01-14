all:
	gcc triangle.c -lm -o triangle -fprofile-arcs -ftest-coverage

clean:
	rm triangle
	rm *.gcno
	rm *.gcda
	rm *.gcov
	rm -f *~

test:
	python27 test.py
	gcov triangle.c

