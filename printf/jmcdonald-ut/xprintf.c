/*
 * xprintf.c
 *
 * Jonathon McDonald - <jmcdonald.ut@gmail.com>
 */
#include <stdio.h>
#include <stdarg.h>

/*
 * Credit due to http://stackoverflow.com/a/12386915 (yeah I'm that guy tonight)
 */
 char * itoa(int value, char *sp, int radix)
 {
     char tmp[16];// be careful with the length of the buffer
     char *tp = tmp;
     int i;
     unsigned v;
     int sign;

     sign = (radix == 10 && value < 0);
     if (sign)   v = -value;
     else    v = (unsigned)value;

     while (v || tp == tmp) {
         i = v % radix;
         v /= radix; // v/=radix uses less CPU clocks than v=v/radix does
         if (i < 10)
           *tp++ = i+'0';
         else
           *tp++ = i + 'a' - 10;
     }

     if (sign) *sp++ = '-';

     while (tp > tmp) *sp++ = *--tp;
 }

void xprintf (const char *fmt, ...)
{
    const char *p;
    va_list argp;
    int i;
    char *s;
    char fmtbuf[256];

    va_start(argp, fmt);

    for (p = fmt; *p != '\0'; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        switch (*++p) {
            case 'c':
                i = va_arg(argp, int);
                putchar(i);
                break;

            case 'd':
                i = va_arg(argp, int);
                s = itoa(i, fmtbuf, 10);
                fputs(s, stdout);
                break;

            case 's':
                s = va_arg(argp, char *);
                fputs(s, stdout);
                break;

            case 'x':
                i = va_arg(argp, int);
                s = itoa(i, fmtbuf, 16);
                fputs(s, stdout);
                break;

            case '%':
                putchar('%');
                break;
        }
    }
}