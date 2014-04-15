.PHONY: clean
CC = clang
CFLAGS = -O0 -g

objects = xprintf.o test.o
bin = test

$(bin): $(objects)

xprintf.o: xprintf.h
test.o: xprintf.h

clean:
	-rm -f $(objects) $(bin)
