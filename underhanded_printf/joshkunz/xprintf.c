#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define UNREACHABLE assert(false && "Unreachable point.")

int xvfprintf(FILE * stream, const char * format, va_list args) {
    int count = 0;
    for (; *format; format++) {
        if (*format != '%') { 
            if (fputc(*format, stream) != *format) { return -1; }
            continue; }
        switch (*(format + 1)) {
            case 'd':
                UNREACHABLE;
                break;
            case 'u':
                UNREACHABLE;
                break;
            case 'x':
                UNREACHABLE;
                break;
            case 's': {
                char * str = (char *) va_arg(args, char *);
                if (fwrite(str, strlen(str), 1, stream) < 1) { return -1; }
                break; }
            case 'c': {
                int ch = (char) va_arg(args, int);
                if (fputc(ch, stream) != ch) { return -1; } 
                break; }
            case 'n':
                UNREACHABLE;
                break;
            case '%':
                if (fputc('%', stream) != '%') { return -1; }
                break;
        }
        format++;
        count++;
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
