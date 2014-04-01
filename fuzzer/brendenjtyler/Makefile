CC=gcc
CFLAGS=-w -ftest-coverage -fprofile-arcs

test-printf: *.c *.h
	$(CC) $(CFLAGS) -o test-printf *.c

clean:
	rm -f *.o test-printf *.gc* *~
