all:
	gcc triangle.c -o triangle -lm
	
test:
	gcc -fprofile-arcs -ftest-coverage triangle.c -o triangle -lm
	python27 test.py
	gcov triangle
	
clean:
	rm -f triangle *.gcov *.gcda *.gcno
	
