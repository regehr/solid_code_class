#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>

/* Macros for stringifying the values of other macros. */
#define __STRINGIFY(x) (#x)
#define STRINGIFY(x) (__STRINGIFY(x))

#define UNREACHABLE assert(false && "Unreachable point.")

#define EXPRINTF (-1)

#define INT_MAXSTRLEN (sizeof(STRINGIFY(INT_MIN)))
#define UINT_MAXSTRLEN (sizeof(STRINGIFY(UINT_MAX)))

void reverses(char * out, int nchars) {
    for (int i = 0; i < (nchars / 2); i++) {
        char tmp = out[i];
        out[i] = out[(nchars - 1) - i];
        out[(nchars - 1) - i] = tmp;
    }
}

int utos(unsigned int v, char * out, bool is_neg) {
    char * _out = out;
    int nchars = 1;
    for (; v > 10; v /= 10, nchars++) {
        *_out++ = '0' + (v % 10);
    }
    *_out++ = '0' + v;
    if (is_neg) { *_out = '-'; nchars++; }
    reverses(out, nchars);
    return nchars;
}

int itos(int v, char * out) {
    /* Note handle INT_MIN case. */
    unsigned int abs_v = v == INT_MIN
                                ? ((unsigned int) INT_MAX) + 1
                                : (unsigned int) abs(v);
    int nchars = utos(abs_v, out, v < 0);
    return nchars;
}

int xvfprintf(FILE * stream, const char * format, va_list args) {
    int count = 0;
    for (; *format; format++) {
        if (*format != '%') { 
            count++;
            if (fputc(*format, stream) != *format) { return EXPRINTF; }
            continue; 
        }
        switch (*(format + 1)) {
            case 'd': {
                char str[INT_MAXSTRLEN] = { '\0' };
                int nchars = itos(va_arg(args, int), str);
                count += nchars;
                if (fwrite(str, nchars, 1, stream) < 1) { return EXPRINTF; }
                break; }
            case 'u': {
                char str[UINT_MAXSTRLEN] = { '\0' };
                int nchars = utos(va_arg(args, unsigned int), str, false);
                count += nchars;
                if (fwrite(str, nchars, 1, stream) < 1) { return EXPRINTF; }
                break; }
            case 'x':
                UNREACHABLE;
                break;
            case 's': {
                char * str = (char *) va_arg(args, char *);
                count += strlen(str);
                if (fwrite(str, strlen(str), 1, stream) < 1) { return EXPRINTF; }
                break; }
            case 'c': {
                int ch = (char) va_arg(args, int);
                count++;
                if (fputc(ch, stream) != ch) { return EXPRINTF; } 
                break; }
            case 'n':
                *(va_arg(args, int *)) = count;
                break;
            case '%':
                count++;
                if (fputc('%', stream) != '%') { return EXPRINTF; }
                break;
        }
        format++;
    }
    return count;
}

int xprintf(const char * format, ...) {
    va_list args;
    va_start(args, format);
    int ret = xvfprintf(stdout, format, args);
    va_end(args);
    return ret;
}
