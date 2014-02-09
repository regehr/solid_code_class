.PHONY: all clean test

bin = huff

generated = compressedTable table testFile.txt testFile.txt.huff \
	testFile.txt.huff.huff

python = python27

all:

clean:
	-rm -f $(generated) $(bin)

test:
	$(python) test.py
