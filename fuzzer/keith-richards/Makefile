CC=gcc
CFLAGS=-O -ftest-coverage -fprofile-arcs

test-printf: *.c *.h
	$(CC) $(CFLAGS) -o test-printf *.c

clean:
	rm -f *.o test-printf *.gcda *.gcno

run:
	./new_fuzz.py
