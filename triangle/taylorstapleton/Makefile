all:
	gcc triangle.c -o triangle -lm
clean:
	rm triangle
	rm triangle.c.gcov
	rm triangle.gcda
	rm triangle.gcno
test:
	gcc -fprofile-arcs -ftest-coverage triangle.c -o triangle -lm
	python27 test.py
	gcov triangle
edit:
	vi triangle.c

testall:
	python27 testAll.py
