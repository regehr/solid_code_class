CC=gcc
CFLAGS=-O
COVFLAGS=-fprofile-arcs -ftest-coverage

all:
	python3 fuzzer.py

coverage:
	python3 fuzzer.py coverage
	gcov vfprintf.c
test-printf: *.c *.h
	$(CC) $(CFLAGS) -o test-printf *.c

c-coverage: *.c *.h
	$(CC) $(CFLAGS) $(COVFLAGS) -o test-printf *.c

clean:
	rm -rf *.o test-printf *.h *.c *.gcda *.gcno *.h.gcov
