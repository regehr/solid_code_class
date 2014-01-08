.PHONY: clean

CC = clang
CFLAGS = -Wall -Wextra -pedantic -Werror
LDLIBS = -lm

bin = triangle

$(bin):

test: $(bin) 
	python fuzz.py 1000

gdb: $(bin) 
	gdb ./$(bin)

clean:
	-rm $(bin) 
