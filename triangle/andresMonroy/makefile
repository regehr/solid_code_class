all: triangle

triangle: triangle.c
	gcc -fprofile-arcs -ftest-coverage -lm -o triangle triangle.c

test: triangle python27 cov

mactest: triangle python cov
	
python27: 
	python27 test.py

python: 
	python test.py

cov:
	gcov triangle
	
clean:
	rm -f triangle triangle.c.gcov triangle.gcda triangle.gcno
	
