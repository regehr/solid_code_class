CC=gcc
AR=ar
CFLAGSPRINT=-coverage -O0
GCOV=gcov



all: 
	$(CC) $(CFLAGSPRINT) -c vfprintf.c -o vfprintf.o
	#$(CC) -c vfprintf.c -o vfprintf.o
	$(CC) -c snprintf.c -o snprintf.o
	$(CC) -c vsnprintf.c -o vsnprintf.o
	$(CC) -c fwrite.c -o fwrite.o
	#$(AR) rcs libPrint.a vfprintf.o snprintf.o vsnprintf.o fwrite.o
	$(GCOV) vfprintf.c

run:
	python27 test.py

cov: 
	$(GCOV) vfprintf.c

clean:
	rm -f *.o *.gcov *.gcno *.gcda *.a
