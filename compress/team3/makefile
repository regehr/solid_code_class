all:
	gcc -g -Wall -std=c99 encoder.c decoder.c decodedOutputFileWriter.c compressedOutputFileWriter.c huff.c -o huff

clean:
	-@rm -rf huff *.txt *.table

test:
	python test.py

check:
	gcc -std=c99 -g -D CHECK_REP encoder.c huff.c -o huff
