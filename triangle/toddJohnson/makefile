all:
	gcc triangle.c -lm -o triangle -fprofile-arcs -ftest-coverage

clean:
	rm -f triangle
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.gcov
	rm -f *~

test:
	python27 test.py
	gcov triangle.c

