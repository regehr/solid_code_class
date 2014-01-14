CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -pedantic -Werror --coverage
LDLIBS = -lgcov

triangle:

test:
	./test.sh

clean:
	-rm triangle triangle.c.gcov triangle.gcda triangle.gcno > /dev/null
