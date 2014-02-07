.PHONY: all clean test

generated = compressedTable table testFile.txt testFile.txt.huff \
	testFile.txt.huff.huff

python = python27

all:

clean:
	-rm $(generated)

test:
	$(python) test.py
