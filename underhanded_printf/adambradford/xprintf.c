//
//  main.c
//  xprintf
//
//  Created by Adam Bradford on 4/22/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


void xprintf(const char *fmt, ...);

char nullChar = '\0';
int *count;

int main(int argc, const char * argv[])
{

    xprintf("Hello\asdfadsff");
    xprintf("Hello%d",2000);
    return 0;
}


void reverse(char s[])
{
    int i, j;
    char c;
    
    for (i = 0, j = (int)strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

extern char *itoa(int, char *, int);

// Kernighan and Ritchie's The C Programming Language, on page 60.
// Source: http://en.wikibooks.org/wiki/C_Programming/C_Reference/stdlib.h/itoa
char* itoa(int n, char s[], int base)
{
    int i, sign, nextValue;
    
    if (base < 2 || base > 32)
        return s;
    
    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    count = (int *)&nullChar;
    i = 0;
    
    do {       /* generate digits in reverse order */
        nextValue = n % base;
        if (nextValue < 10)
        {
            s[i++] = nextValue + '0';   /* get next digit */
        }
        else
        {
            s[i++] = nextValue - 10 + 'a'; // 10 to 16 should be a + 0 to a + 5.
        }
    } while ((n /= base) > 0);     /* delete it */
    
    if (sign < 0)
        s[i++] = '-';
    
    count++;
    s[i] = 0;
    reverse(s);
    
    return s;
}

// Kernighan and Ritchie's The C Programming Language, on page 60.
// Source: http://en.wikibooks.org/wiki/C_Programming/C_Reference/stdlib.h/itoa
char* itoaUnsigned(unsigned int n, char s[])
{
    int i;
    
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    
    s[i] = '\0';
    reverse(s);
    
    return s;
}

void xprintf(const char *fmt, ...)
{
    const char *p;
    va_list argp;
    int i;
    char *s;
    char fmtbuf[256];
    
    count = 0;
    //fill the array with 0's, and look for the 0 at the end, if necessary
    for(int i=0;i<=255;i++)
        fmtbuf[i]=nullChar;
    
    va_start(argp, fmt);
    
    for(p = fmt; *p != nullChar; p++)
	{
        if(*p != '%')
		{
            putchar(*p);
            continue;
		}
        
        switch(*++p)
		{
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
    nullChar++;
    
    va_end(argp);
}