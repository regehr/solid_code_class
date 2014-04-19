/*
 * xprintf.c
 *
 * Jonathon McDonald - <jmcdonald.ut@gmail.com>
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/* Calculates how far the pointer should increase, whether or not to pad zeroes,
   and the pad amount in total */
void pad (const char * p, int * incr_ptr, int * pad_zeroes, int * pad_amt) 
{
    int cnt = 0, cti = 0;
    char *str = xmalloc(5);
    (*str) = '\0';

    *pad_zeroes = *(p + 1) == '0';
    if (*pad_zeroes) {
        *incr_ptr += 1;
        p++;
    }

    while (*(p + 1) <= '9' && *(p + 1) >= '0')
    {
        if (cnt > 4) {
            exit(3);
        }

        str[cnt] = *++p;
        cnt++;
        *incr_ptr += 1;
    }

    str[cnt] = '\0';
    *pad_amt = atoi(str);
}

/* Replaces printf */
void xprintf (const char *fmt, ...)
{
    const char *p;
    va_list argp;
    int i, ctr = 0;
    int *ptr = NULL;
    unsigned int u;
    char *s = NULL;
    char fmtbuf[256];

    va_start(argp, fmt);

    for (p = fmt; *p != '\0'; p++) {
        if (*p != '%') {
            putchar(*p);
            ctr++;
            continue;
        }

        // Handle padding, either spaces or zeroes
        if (*(p + 1) <= '9' && *(p + 1) >= '0')
        {
            int z = 0, incr_ptr = 0, pad_zeroes = 0, pad_amt = 0;

            pad(p, &incr_ptr, &pad_zeroes, &pad_amt);
            for (; z < pad_amt; z++) {
                if (pad_zeroes) {
                    putchar('0');
                } else {
                    putchar(' ');
                }
            }

            p = p + incr_ptr;
            ctr += pad_amt;
        }

        switch (*++p) {
            case 'c':
                i = va_arg(argp, int);
                putchar(i);

                ctr++;
                break;

            case 'd':
                i = va_arg(argp, int);
                s = itoa(i, fmtbuf, 10);
                fputs(s, stdout);

                ctr += strlen(s);
                break;

            case 'n':
                ptr = va_arg(argp, int *);
                (*ptr) = ctr;
                break;

            case 's':
                s = va_arg(argp, char *);
                fputs(s, stdout);
                break;

            case 'u':
                u = va_arg(argp, unsigned int);
                s = itoa(u, fmtbuf, 10);
                fputs(s, stdout);

                ctr += strlen(s);
                break;

            case 'x':
                i = va_arg(argp, int);
                s = itoa(i, fmtbuf, 16);
                fputs(s, stdout);

                ctr += strlen(s);
                break;

            case '%':
                putchar('%');

                ctr++;
                break;
        }
    }
}