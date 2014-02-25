

CC = clang
CFLAGS = -Wall -g  #-fsanitize=undefined

BINARY = rhuff

COMPILE = $(CC) $(CFLAGS) -c
OBJFILES := $(patsubst %.c,%.o,$(wildcard *.c))

ALL_C_FILES = $(shell find ../.. -name '*.c')
ALL_H_FILES = $(shell find ../.. -name '*.h')
ALL_P_FILES = $(shell find ../.. -name '*.py')



all: $(BINARY)

$(BINARY): $(OBJFILES)
	$(CC) -o $(BINARY) $(OBJFILES)

%.o: %.c
	$(COMPILE) -o $@ $< 

clean:
	-@rm -f $(OBJFILES)
	-@rm -f $(BINARY)
	-@rm -f interFile

test:
	$(PY) test.py


.PHONY: check

check: $(BINARY)
	@for file in $(ALL_C_FILES) ; do ./huff -t $$file check 1> /dev/null ; done
	@for file in $(ALL_H_FILES) ; do ./huff -t $$file check 1> /dev/null ; done
	@for file in $(ALL_P_FILES) ; do ./huff -t $$file check 1> /dev/null ; done

rle: testMain.c testMainD.c rhuff_compress.c rhuff_decompress.c
	gcc -o rle testMain.c rhuff_compress.c
	gcc -o rled testMainD.c rhuff_decompress.c 
