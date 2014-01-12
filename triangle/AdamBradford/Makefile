all:
	gcc main.c triangle.c -o triangle -lm -fprofile-arcs -ftest-coverage
clean:
	rm triangle 
	rm *.gcno
	rm *.gcda
	rm *.gcov
test:
	python27 test.py
	gcov triangle.c

