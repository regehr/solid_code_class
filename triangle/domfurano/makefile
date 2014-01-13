all:
	gcc -O0 -Werror -Wall triangle.c -lm -o triangle
clean:
	@rm -f triangle
	@rm -f *~
	@rm -f *gcov
	@rm -f *gcno
	@rm -f *gcda
test:
	@make clean
	@gcc -O0 -fprofile-arcs -ftest-coverage triangle.c -lm -o triangle
	@python test.py
	@gcov triangle.gcda
coverage:
	@make test
	@cat triangle.c.gcov
