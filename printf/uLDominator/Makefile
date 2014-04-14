all:
	gcc -c xprintf.c -o xprintf.o
	gcc test.c xprintf.o -o test
	
test: all
	./test
	
clean:
	rm *.o
	rm test