.PHONY: clean
CC = clang
CFLAGS = -O0

objects = xprintf.o test.o

test: $(objects)

xprintf.o: xprintf.h
test.o: xprintf.h

clean:
	-rm -f $(objects)
