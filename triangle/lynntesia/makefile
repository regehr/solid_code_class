all:
	gcc -Wall triangle.c -lm -o triangle -fprofile-arcs -ftest-coverage
clean:
	rm -f triangle *.gcov *.gcda *.gnco
test:
	./test.sh
	gcov -b triangle.c