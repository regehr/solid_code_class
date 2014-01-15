all:
	gcc triangle.c -o triangle -lm
	
coverage:
	gcc -fprofile-arcs -ftest-coverage triangle.c -o triangle -lm
	
test: all
	python27 test.py
	
clean:
	rm triangle triangle.c.gc* triangle.gc* *~
