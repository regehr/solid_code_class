triangle: triangle.c
	gcc -fprofile-arcs -ftest-coverage triangle.c -o triangle

test:
	./test.sh
	gcov -b triangle.c

clean:
	rm -rf triangle *.gcda *.gcov *.gcno *~
