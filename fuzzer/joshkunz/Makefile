.PHONY: both cov clean

MUSL_BASE = ../musl-printf-standalone
MUSL_EXCLUDE = test-printf.c
MUSL_LOCAL = musl

coverage = vfprintf

CC = gcc 
CFLAGS = -O0 -Wall -Wno-trigraphs -Wno-unused -w
MUSL_CFLAGS = -I$(MUSL_BASE)/ -fprofile-arcs -ftest-coverage
LDLIBS = -lm

MUSL_SRC = $(filter-out $(MUSL_EXCLUDE),$(notdir $(wildcard $(MUSL_BASE)/*.c)))
MUSL_OBJS = $(addprefix $(MUSL_LOCAL)/,$(patsubst %.c,%.o,$(MUSL_SRC)))


both: test-musl test-local

cov: $(MUSL_LOCAL)/$(coverage).g*
	gcov -b $(MUSL_LOCAL)/$(coverage)

$(MUSL_LOCAL):
	mkdir $(MUSL_LOCAL)

$(MUSL_LOCAL)/%.o: $(MUSL_BASE)/%.c $(MUSL_BASE)/musl.h | $(MUSL_LOCAL)
	$(CC) $(MUSL_CFLAGS) $(CFLAGS) -c -o $@ $<

test-musl: test.c $(MUSL_OBJS) $(MUSL_BASE)/musl.h
	$(CC) $(MUSL_CFLAGS) $(CFLAGS) -DMUSL $(LDLIBS) $(MUSL_OBJS) -o $@ $<

test-local: test.c 
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $<

clean:
	-rm -f test-musl test-local
	-rm -rf $(MUSL_LOCAL)
	-rm *.c *.out
	-rm -f *.gcda *.gcno *.gcov
