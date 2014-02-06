
CC = clang
CFLAGS = -Wall -g #-fsanitize=undefined

BINARY = huff

COMPILE = $(CC) $(CFLAGS) -c
OBJFILES := $(patsubst %.c,%.o,$(wildcard *.c))

ALL_FILES = $(shell find ../../ -name '*.c')



all: $(BINARY)

$(BINARY): $(OBJFILES)
	$(CC) -o $(BINARY) $(OBJFILES)

%.o: %.c
	$(COMPILE) -o$@ $< 

clean:
	-@rm -f $(OBJFILES)
	-@rm -f $(BINARY)



.PHONY: check

check: $(BINARY)
	@for file in $(ALL_FILES) ; do ./huff -t $$file check ; done