CC = musl/bin/musl-gcc
CFLAGS = -Wall -Werror -O3 -static -std=c99 -g
COVFLAGS = -fprofile-arcs -ftest-coverage

BIN = fuzzer
SRCS = fuzzer.c
OBJS = ${SRCS:.c=.o}
DEPS = ${SRCS:.c=.d}

${BIN}: ${OBJS}
	${CC} ${FLAGS} -o ${BIN} ${OBJS}

${BIN}-cov: ${OBJS}
	${CC} ${FLAGS} ${COVFLAGS} -o ${BIN}-cov ${OBJS}
	
.PHONY: cov
cov: ${BIN}-cov
	./${BIN}-cov -t test.txt
	gcov ${BIN}-cov
	
val: ${BIN} test.txt
	valgrind --leak-check=yes ./${BIN} -t test.txt

.PHONY: clean
clean:
	@rm -f ${BIN} ${OBJS} ${DEPS} *.gcov *.gcno *.gcda *~
