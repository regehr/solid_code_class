all:
	gcc triangle.c -o triangle -lm
	
test:
	gcc -fprofile-arcs -ftest-coverage triangle.c -o triangle -lm
	python27 test.py
	gcov triangle
	
clean:
	rm triangle triangle.c.gcov triangle.gcda triangle.gcno
	
