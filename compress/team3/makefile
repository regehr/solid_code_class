.PHONY: all clean test debug

CC = clang
CFLAGS = -std=c99'

objects = syscalls.o encoder.o decoder.o decodedOutputFileWriter.o \
encodedOutputFileWriter.o huff.o

bin = huff

all: $(bin)

$(bin): $(objects)

clean:
	-@rm -rf $(bin) $(objects) *.txt *.table *.huff

test: debug
	python test.py

debug: clean
	$(MAKE) CFLAGS='-Wall -Wextra -pedantic -std=c99 -g -DCHECK_REP'

release: clean
	$(MAKE) CFLAGS='-std=c99 -DNDEBUG'
