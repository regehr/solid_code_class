all:
	gcc -g -Wall -std=c99 encoder.c decoder.c decodedOutputFileWriter.c compressedOutputFileWriter.c huff.c -o huff

clean:
	-@rm -rf huff *.txt *.table *.huff

test:
	python test.py

check:
	gcc -g -Wall -std=c99 -D CHECK_REP encoder.c decoder.c decodedOutputFileWriter.c compressedOutputFileWriter.c huff.c -o huff


