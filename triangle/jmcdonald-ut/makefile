all: 
	gcc triangle.c -o triangle -lm

test:
	gcc triangle.c -o triangle -lm -fprofile-arcs -ftest-coverage
	ruby ./tester.rb
	gcov triangle

clean:
	rm ./triangle
	rm ./triangle.c.gcov	
	rm ./triangle.gcda	
	rm ./triangle.gcno
