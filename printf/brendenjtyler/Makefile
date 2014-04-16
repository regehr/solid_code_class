CC=gcc
CFLAGS= -lm -w
DBFLAGS = -g

all:
	$(CC) xprintf.c $(CFLAGS) -o xprintf 

db:
	$(CC) xprintf.c $(CFLAGS) $(DBFLAGS) -o xprintf

clean:
	rm -f *.o xprintf *~
