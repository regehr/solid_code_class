.PHONY: clean
CC = clang
CFLAGS = -O0 -g -Wall -Wextra -pedantic
LDLIBS = -lm

objects = xprintf.o test.o
bin = test

run-tests: $(bin)
	./test

$(bin): $(objects)

xprintf.o: xprintf.h
test.o: xprintf.h

clean:
	-rm -f $(objects) $(bin)
