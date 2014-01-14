all:
	gcc triangle.c -o triangle -fprofile-arcs -ftest-coverage

clean:
	rm triangle triangle.c.gcov triangle.gcda triangle.gcno

test:
	
	./triangle 10 17 12 8 10 14
	
	./triangle 3 4 5 1 2 9
	
	./triangle 10 15 46 78 23 1

	./triangle 83 44 19 23 32 45
	
	./triangle 49 68 21 10 82 39
	
	./triangle 0 0 0 5 5 0
	
	./triangle 0 0 0 0 0 0

	gcov -b triangle
	