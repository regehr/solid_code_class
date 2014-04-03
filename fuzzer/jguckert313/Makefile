CC=gcc
CFLAGSPRINT=-ftest-coverage -O0 -fprofile-arcs
GCOV=gcov



all: 
	$(CC) $(CFLAGSPRINT) -c vfprintf.c -o vfprintf.o
	$(CC) $(CFLAGSPRINT) -c snprintf.c -o snprintf.o
	$(CC) $(CFLAGSPRINT) -c vsnprintf.c -o vsnprintf.o
	$(CC) $(CFLAGSPRINT) -c fwrite.c -o fwrite.o
	$(CC) $(CFLAGSPRINT) fwrite.o vsnprintf.o snprintf.o vfprintf.o test_printf.c -o fuzzer
	./fuzzer


py:
	python27 fuzzer.py

cover: 
	$(GCOV) vfprintf.c

clean:
	rm -f *.o *.gcov *.gcno *.gcda *.a fuzzer
	rm test_printf.c

