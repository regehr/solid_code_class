.PHONY: clean

CC = clang
CFLAGS = -Wall -Wextra -pedantic -Werror
LDLIBS = -lm

bin = triangle
test_file = outputs.text

$(bin):

test: $(bin) 
	python test.py --test $(test_file)
	python test.py --fuzz 100

gdb: $(bin) 
	gdb ./$(bin)

clean:
	-rm $(bin) 
