CC = gcc
CFLAGS = -w -std=c99
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

test: *.c *.h
	$(CC) $(CFLAGS) -DMUSL -o test_musl *.c
	$(CC) $(CFLAGS) -o test_local *.c

clean:
	@rm -f *.o test_local test_musl *.gcda *.gcno *.gcov *~ *.txt
	@echo 'In Soviet Russia, make cleans you!'

coverage:
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) -DMUSL -o test_musl *.c
	@./test_musl > /dev/null
	gcov vfprintf.c
