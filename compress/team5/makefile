
CC = clang
CFLAGS = -Wall -O2 -g
OPTIONAL_CFLAGS = -fsanitize=undefined,unsigned-integer-overflow

BINARY = huff

COMPILE = $(CC) $(CFLAGS) -c
OBJFILES := $(patsubst %.c,%.o,$(wildcard *.c))

all: $(BINARY)

$(BINARY): $(OBJFILES)
	$(CC) -o $(BINARY) $(OBJFILES)

%.o: %.c
	$(COMPILE) -o $@ $< 

clean:
	-@rm -f $(OBJFILES)
	-@rm -f $(BINARY)

test: $(BINARY)
	@echo "no tests quite yet\n"