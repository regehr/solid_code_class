.PHONY: clean

CC = clang
CFLAGS = -Wall -Wextra

objects = main.o
bin = huff

mail.o: huff.h

$(bin): $(objects) 
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

clean:
	-rm $(bin) $(objects)
