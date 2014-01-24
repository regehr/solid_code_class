all: triangle.c
	gcc -std=c99 triangle.c -o triangle
clean:
	@rm -f triangle *~ *gcov *gcno *gcda
test:
	@make clean
	@gcc -m32 -O2 -fprofile-arcs -ftest-coverage triangle.c -lm -o triangle
	@python27 test.py
	@gcov triangle.gcda
coverage:
	@cat triangle.c.gcov
