CC=gcc
CFLAGS=-O
COVFLAGS=-fprofile-arcs -ftest-coverage

all:
	python3 fuzzer.py coverage

coverage: all
	$(CC) $(COVFLAGS) *.c
	./a.out > /dev/null
	gcov vfprintf.c
	make clean
	
test-printf: *.c *.h
	$(CC) *.c

c-coverage: *.c *.h
	$(CC)  $(COVFLAGS) *.c

clean:
	-@rm -rf *.o 
	-@rm -rf a.out
	-@rm -rf *.h 
	-@rm -rf *.c 
	-@rm -rf *.gcda 
	-@rm -rf *.gcno 
	-@rm -rf *.h.gcov
	-@rm -rf *~
