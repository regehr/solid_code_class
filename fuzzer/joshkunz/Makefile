.PHONY: both cov clean

MUSL_BASE = ../musl-printf-standalone
SPENCER_BASE = ../sphippen

MUSL_LOCAL = musl
MUSL_SRC = $(addprefix $(MUSL_LOCAL)/, \
             fwrite.c snprintf.c vsnprintf.c vfprintf-fixed.c)
MUSL_OBJS = $(patsubst %.c,%.o,$(MUSL_SRC))

vpath %.c $(MUSL_BASE):$(SPENCER_BASE)

CC = gcc 
CFLAGS = -O0 -Wall -Wno-trigraphs -Wno-unused -w
MUSL_CFLAGS = -I$(MUSL_BASE)/ -fprofile-arcs -ftest-coverage
LDLIBS = -lm

both: test-musl test-local

cov: $(MUSL_LOCAL)/vfprintf-fixed.g*
	gcov -b $(MUSL_LOCAL)/vfprintf-fixed

$(MUSL_LOCAL):
	mkdir $(MUSL_LOCAL)

$(MUSL_LOCAL)/%.o: %.c $(MUSL_BASE)/musl.h | $(MUSL_LOCAL)
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
