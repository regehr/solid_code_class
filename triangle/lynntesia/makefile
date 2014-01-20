all:
	gcc -Wall triangle.c -lm -o triangle -fprofile-arcs -ftest-coverage
clean:
	rm -f triangle *.gcov *.gcda *.gcno
test:
	python27 test.py
	gcov -b triangle.c