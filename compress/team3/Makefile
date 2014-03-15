.PHONY: all clean test debug

RKT = racket

CC = clang
CFLAGS = -std=c99 -O3 -Wall -Wextra -Wno-unused -Wno-unused-parameter

objects = syscalls.o encoder.o decoder.o decodedOutputFileWriter.o \
encodedOutputFileWriter.o rhuff.o

test_file = tester.rkt

bin = rhuff
test_dir = tests

all: $(bin)

$(bin): $(objects)

clean:
	-rm -f $(bin) $(objects) *.txt *.table *.huff
	-rm -rf $(bin).dSYM
	# clean the test-generated files.
	-rm -f $(test_dir)/*.input
	-rm -f $(test_dir)/$(bin)

test: debug
	cp $(bin) $(test_dir)
	cd $(test_dir) && $(RKT) $(test_file)

debug: clean
	$(MAKE) CFLAGS='-Wall -Wextra -pedantic -std=c99 -g -DCHECK_REP'

release: clean
	$(MAKE) CFLAGS='$(CFLAGS) -DNDEBUG'

