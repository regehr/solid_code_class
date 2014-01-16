all: triangle.c
	gcc -m32 -O0 -Werror -Wall triangle.c -lm -o triangle
clean:
	@rm -f triangle *~ *gcov *gcno *gcda
test:
	@make clean
	@gcc -m32 -O0 -fprofile-arcs -ftest-coverage triangle.c -lm -o triangle
	@python27 test.py
	@gcov triangle.gcda
coverage:
	@cat triangle.c.gcov
