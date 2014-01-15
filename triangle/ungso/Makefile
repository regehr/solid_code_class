test:
	gcc -g -fprofile-arcs -ftest-coverage -o triangle triangle.c -lm
	python27 test.py


clean:
	-@rm -rf triangle *.gcda *.gcno *.gcov 2>/dev/null