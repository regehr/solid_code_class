#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>

#define UNREACHABLE assert(false && "Unreachable point.")
#define EXPRINTF (-1)

#define MAXSTRLEN (((int) ceil(log10((double) UINT_MAX))) + 1)

void reverses(char * out, int nchars) {
    assert(nchars >= 0);
    for (int i = 0; i < (nchars / 2); i++) {
        char tmp = out[i];
        out[i] = out[(nchars - 1) - i];
        out[(nchars - 1) - i] = tmp;
    }
}

char cfori(int i) {
    assert(i >= 0 && i <= 32);
    return i < 10 ? '0' + i : 'a' + (i - 10);
}

int utos(unsigned int v, char * out, int radix, bool is_neg) {
    char * _out = out;
    int nchars = 1;
    for (; v > radix; v /= radix, nchars++) {
        *_out++ = cfori(v % radix);
    }
    *_out++ = cfori(v);
    if (is_neg) { *_out = '-'; nchars++; }
    reverses(out, nchars);
    out[nchars] = '\0';
    return nchars;
}

unsigned int xabs(int i) {
    return i == INT_MIN
        ? ((unsigned int) INT_MAX) + 1
        : (unsigned int) abs(i);
}

int itos(int v, char * out) {
    /* Note handle INT_MIN case. */
    int nchars = utos(xabs(v), out, 10, v < 0);
    return nchars;
}

int field_width(const char ** fmt) {
    const char * format = *fmt;
    int fw = 0;
    for (; *format && isdigit(*format); format++) {
        fw *= 10;
        fw += *format - '0';
    }
    *fmt = format;
    return fw;
}

char * pad(int c, int fw, int len, char * fwb, char * str) {
    memset(fwb, c, fw);
    fwb[fw] = '\0';
    if (fw > len) {
        memcpy(&fwb[fw] - len, str, len);
        return fwb;
    } else {
        return str;
    }
}

int xvfprintf(FILE * stream, const char * format, va_list args) {
    int count = 0;
    char str[MAXSTRLEN];
    memset(str, '\0', MAXSTRLEN);
    char * str_out = NULL;
    int nchars = -1;

    for (; *format; format++) {
        if (*format != '%') { 
            count++;
            if (fputc(*format, stream) != *format) { return EXPRINTF; }
            continue; 
        }

        format++;
        int fw = field_width(&format);
        char fwb[fw + 1];
        //printf("Got fw: %d\n",  fw);

        switch (*format) {
            case 'd':
                nchars = itos(va_arg(args, int), str);
                str_out = pad(' ', fw, nchars, fwb, str);
                break;
            case 'u':
                nchars = utos(va_arg(args, unsigned int), str, 10, false);
                str_out = pad(' ', fw, nchars, fwb, str);
                break;
            case 'x': 
                nchars = utos(va_arg(args, unsigned int), str, 16, false);
                str_out = pad(' ', fw, nchars, fwb, str);
                break;
            case 's': 
                str_out = (char *) va_arg(args, char *);
                str_out = pad(' ', fw, strlen(str_out), fwb, str_out);
                break;
            case 'c':
                str[0] = (char) va_arg(args, int);
                str_out = pad(' ', fw, 1, fwb, str);
                break;
            case 'n':
                *(va_arg(args, int *)) = count;
                break;
            case '%':
                str[0] = '%';
                str_out = pad(' ', fw, 1, fwb, str);
                break;
        }
        if (str_out == NULL) { str_out = str; }

        count += strlen(str_out);
        if (strlen(str_out) > 0 && 
                fwrite(str_out, strlen(str_out), 1, stream) < 1) { 
            return EXPRINTF; 
        }

        memset(str, '\0', MAXSTRLEN);
        str_out = NULL;
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
