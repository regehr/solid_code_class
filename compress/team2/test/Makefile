.PHONY: default clean test

bin = huff

generated = compressedTable table testFile.txt testFile.txt.huff \
	testFile.txt.huff.huff

PY = python27

default:

clean:
	-rm -f $(generated) $(bin)

test:
	$(PY) test.py
