all:
	gcc -std=c99 main.c encoder.c decoder.c -o huff

clean:
	-@rm -rf huff *.txt *.table

test:
	python test.py

check:
	gcc -std=c99 -g -D CHECK_REP main.c encoder.c decoder.c -o huff
