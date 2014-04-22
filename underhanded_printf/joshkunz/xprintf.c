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

void swap(int what, int with, char * out) {
    char tmp = out[what];
    out[what] = out[with];
    out[with] = tmp;
}

void reverse(char * out, int nchars) {
    assert(nchars >= 0);
    for (int i = 0; i < (nchars / 2); i++) {
        swap(i, (nchars - 1) - i, out);
    }
}

char cfori(int i) {
    assert(i >= 0 && i <= 32);
    return i < 10 ? '0' + i : 'a' + (i - 10);
}

int utos(unsigned int v, char * out, unsigned int radix) {
    assert(radix >= 0 && radix <= 32);
    int nchars = 0;
    for (; v > radix; v /= radix, nchars++) {
        out[nchars] = cfori(v % radix);
    }
    out[nchars++] = cfori(v);
    reverse(out, nchars);
    out[nchars] = '\0';
    return nchars;
}

/* abs function that actually handles the INT_MIN case. */
unsigned int xabs(int i) {
    return i == INT_MIN
        ? ((unsigned int) INT_MAX) + 1
        : (unsigned int) abs(i);
}

int itos(int v, char * out) {
    int nchars = utos(xabs(v), out, 10);
    if (v < 0) {
        memmove(out + 1, out, nchars++);
        out[0] = '-';
    }
    return nchars;
}

int field_width(const char ** fmt) {
    const char * format = *fmt;
    int fw = 0;
    if (*format && *format == '0') { return fw; }
    for (; *format && isdigit(*format); format++) {
        fw *= 10;
        fw += *format - '0';
    }
    *fmt = format;
    return fw;
}

char * pad(int c, int fw, char * fwb, char * str) {
    int len = strlen(str);
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
    char * str_out = NULL;

    for (; *format; format++) {
        memset(str, 0, MAXSTRLEN);

        if (*format != '%') { 
            count++;
            if (fputc(*format, stream) != *format) { return EXPRINTF; }
            continue; 
        }

        if (!*++format) { return EXPRINTF; }
        int padc = ' ';
        if (*format == '0') {
            padc = '0';
            if (!*++format) { return EXPRINTF; };
        }

        int fw = field_width(&format);
        char fwb[fw + 1];

        switch (*format) {
            case 'd':
                (void) itos(va_arg(args, int), str);
                str_out = pad(padc, fw, fwb, str);
                if (padc == '0' && str[0] == '-' && str_out == fwb)
                    swap(0, fw - strlen(str), str_out);
                break;
            case 'u':
                (void) utos(va_arg(args, unsigned int), str, 10);
                str_out = pad(padc, fw, fwb, str);
                break;
            case 'x': 
                (void) utos(va_arg(args, unsigned int), str, 16);
                str_out = pad(padc, fw, fwb, str);
                break;
            case 's': 
                str_out = pad(' ', fw, fwb, va_arg(args, char *));
                break;
            case 'c':
                str[0] = (char) va_arg(args, int);
                str_out = pad(' ', fw, fwb, str);
                break;
            case 'n':
                *(va_arg(args, int *)) = count;
                continue;
            case '%':
                str[0] = '%';
                str_out = pad(' ', fw, fwb, str);
                break;
            default: UNREACHABLE;
        }

        count += strlen(str_out);
        if (strlen(str_out) > 0 && 
                fwrite(str_out, strlen(str_out), 1, stream) < 1) { 
            return EXPRINTF; 
        }
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
