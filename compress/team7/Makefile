CC = gcc
CFLAGS = -Wall -MMD -std=c99 -g -Werror -O3
COVFLAGS = -fprofile-arcs -ftest-coverage
BIN = rhuff
LIBS = -lm
SRCS = huff.c huff_table.c util.c
OBJS = ${SRCS:.c=.o}
DEPS = ${SRCS:.c=.d}

${BIN}: ${OBJS}
	${CC} ${CFLAGS} -o ${BIN} ${OBJS} ${LIBS}

${BIN}-cov: ${OBJS}
	${CC} ${CFLAGS} ${COVFLAGS} -o ${BIN}-cov ${OBJS} ${LIBS}

.PHONY: cov
cov: ${BIN}-cov
	./${BIN}-cov -t test.txt
	gcov ${BIN}-cov

val: ${BIN} test.txt
	valgrind --leak-check=yes ./${BIN} -t test.txt

files: generateFiles.py
	python27 generateFiles.py

.PHONY: clean
clean:
	@rm -f ${BIN} ${OBJS} ${DEPS} *.gcov *.gcno *.gcda
	@rm -rf files/*
