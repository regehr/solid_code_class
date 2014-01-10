.PHONY: clean

CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -pedantic -Werror
CFLAGS += -ftest-coverage -fprofile-arcs
LDLIBS = -lm

bin = triangle
test_file = outputs.text

$(bin):

test: $(bin) 
	python test.py --file $(test_file) ./$(bin)
	gcov -b $(bin)

gdb: $(bin) 
	gdb ./$(bin)

clean:
	-rm $(bin) 
	-rm *.gcov *.gcda *.gcno
