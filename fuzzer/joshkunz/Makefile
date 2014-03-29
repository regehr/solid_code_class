MUSL_BASE = ../musl-printf-standalone
SPENCER_BASE = ../sphippen

MUSL_EXCLUDE = $(MUSL_BASE)/test-printf.c $(MUSL_BASE)/vfprintf.c
MUSL_SRC = $(filter-out $(MUSL_EXCLUDE),$(wildcard $(MUSL_BASE)/*.c)) \
		   $(SPENCER_BASE)/vfprintf-fixed.c

CC = gcc
CFLAGS = -Wno-trigraph
LDLIBS = -lm

both: test-musl test-local

test-musl: test.c $(MUSL_SRC) $(MUSL_BASE)/musl.h
	$(CC) $(CFLAGS) -DMUSL $(LDLIBS) -o $@ $< $(MUSL_SRC)

test-local: test.c 
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $<

clean:
	-rm -f test-musl test-local
	-rm *.c *.out
