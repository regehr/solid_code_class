all:
	gcc -std=c99 encoder.c huff.c -o huff

clean:
	-@rm -rf huff *.txt *.table

test:
	python test.py
