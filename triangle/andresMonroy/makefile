all:
	gcc triangle.c  -lm -o triangle

test:
	gcc -fprofile-arcs -ftest-coverage triangle.c -o triangle -lm
	python27 test.py
	gcov triangle

testmac:
	gcc -fprofile-arcs -ftest-coverage triangle.c -o triangle
	python test.py
	gcov triangle
clean:
	rm triangle triangle.c.gcov triangle.gcda triangle.gcno
	
