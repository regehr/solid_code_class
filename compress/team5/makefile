
CC = clang
CFLAGS = -Wall -O2 -fsanitize=undefined,unsigned-integer-overflow

BINARY = maketable

COMPILE = $(CC) $(CFLAGS) -c
OBJFILES := $(patsubst %.c,%.o,$(wildcard *.c))

all: $(BINARY)

$(BINARY): $(OBJFILES)
	$(CC) -o $(BINARY) $(OBJFILES)

%.o: %.cpp
	$(COMPILE) -o $@ $< 

clean:
	-rm -f $(OBJFILES)