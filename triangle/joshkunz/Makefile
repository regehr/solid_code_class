.PHONY: clean

CC = clang
CFLAGS = -Wall -Wextra -pedantic -Werror
LDLIBS = -lm

bin = triangle
test_file = outputs.text

$(bin):

test: $(bin) 
	python test.py --file $(test_file) ./$(bin)
	python test.py --fuzz 100 ./$(bin)

gdb: $(bin) 
	gdb ./$(bin)

clean:
	-rm $(bin) 
