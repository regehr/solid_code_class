MUSL_BASE = ../musl-printf-standalone
MUSL_SRC = $(filter-out $(MUSL_BASE)/test-printf.c,$(wildcard $(MUSL_BASE)/*.c))

CC = gcc
CFLAGS = -w
LDLIBS = -lm

both: test-musl test-local

test-musl: test.c $(MUSL_SRC) $(MUSL_BASE)/musl.h
	$(CC) $(CFLAGS) -DMUSL $(LDLIBS) -o $@ $< $(MUSL_SRC)

test-local: test.c 
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $<

clean:
	-rm -f test-musl test-local
	-rm *.c *.out
