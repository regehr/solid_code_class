#define restrict

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

typedef struct __MUSL_FILE {
	unsigned flags;
	unsigned char *rpos, *rend;
	int (*close)(struct __MUSL_FILE *);
	unsigned char *wend, *wpos;
	unsigned char *mustbezero_1;
	unsigned char *wbase;
	size_t (*read)(struct __MUSL_FILE *, unsigned char *, size_t);
	size_t (*write)(struct __MUSL_FILE *, const unsigned char *, size_t);
	off_t (*seek)(struct __MUSL_FILE *, off_t, int);
	unsigned char *buf;
	size_t buf_size;
	struct __MUSL_FILE *prev, *next;
	int fd;
	int pipe_pid;
	long lockcount;
	short dummy3;
	signed char mode;
	signed char lbf;
	int lock;
	int waiters;
	void *cookie;
	off_t off;
	char *getln_buf;
	void *mustbezero_2;
	unsigned char *shend;
	off_t shlim, shcnt;
} MUSL_FILE;


extern size_t __fwritex(const unsigned char *restrict s, size_t l, MUSL_FILE *restrict f);
extern int musl_printf(const char *restrict fmt, ...);
extern int musl_vfprintf(MUSL_FILE *restrict f, const char *restrict fmt, va_list ap);
extern int musl_snprintf(char *restrict s, size_t n, const char *restrict fmt, ...);
extern int musl_vsnprintf(char *restrict s, size_t n, const char *restrict fmt, va_list ap);

#define NL_ARGMAX 9

