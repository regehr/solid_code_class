#compiler to use
CC=gcc

#compiler options
CFLAGS= -lm -O2
TESTFLAGS = -fprofile-arcs -ftest-coverage
DBFLAGS = -lm -g

#source and executable files
SOURCE= triangle.c
EXECUTABLE= -o triangle
all:
	$(CC) $(SOURCE) $(EXECUTABLE) $(CFLAGS)

db:
	$(CC) $(SOURCE) $(EXECUTABLE) $(DBFLAGS)

test:
	$(CC) $(SOURCE) $(EXECUTABLE) $(CFLAGS) $(TESTFLAGS)
	python3 tests.py

clean:
	rm -rf *o *gcda *gcno *gcov triangle

superclean:
	rm -rf *o *gcda *gcno *gcov *~ triangle
