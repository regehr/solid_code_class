#include <stdio.h>
#include <stdarg.h>

//Taken from: http://lib.psyc.eu/doc/itoa_8c_source.html
#define ALPHANUMS "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"
int itoa(int number, char* out, int base) 
{
    int t, count;
    char *p, *q;
    char c;

    p = q = out;
    if (base < 2 || base > 36) 
		base = 10;
 
    do 
	{
       t = number;
       number /= base;
       if (out) *p = ALPHANUMS[t+35 - number*base];
       p++;
    } while (number);
 
    if (t < 0) 
	{
        if (out) *p = '-';
        p++;
    }
	
    count = p-out;
    if (out) 
	{
        *p-- = '\0';
        while(q < p) 
		{
            c = *p;
            *p-- = *q;
            *q++ = c;
        }
    }
	
    return count;
}

void xprintf(const char *fmt, ...)
{
	const char *p;
	va_list argp;
	int i;
	char *s;
	char fmtbuf[256];

	va_start(argp, fmt);

	for(p = fmt; *p != '\0'; p++)
	{
		if(*p != '%')
		{
			putchar(*p);
			continue;
		}

		switch(*++p)
		{
			//Char
			case 'c':
				i = va_arg(argp, int);
				putchar(i);
				break;

			//Int (base 10)
			case 'd':
				i = va_arg(argp, int);
				itoa(i, fmtbuf, 10);
				fputs(fmtbuf, stdout);
				break;

			//String
			case 's':
				s = va_arg(argp, char *);
				fputs(s, stdout);
				break;

			//Int (base 16)
			case 'x':
				i = va_arg(argp, int);
				itoa(i, fmtbuf, 16);
				fputs(fmtbuf, stdout);
				break;

			//ugh
			case '%':
				putchar('%');
				break;
				
			//Unsigned Int (base 10)
			case 'u':
				break;
				
			//Nothing printed case
			//Argument is a pointer to a signed int
			//Store number of chars written so far in argument
			case 'n':
				break;
		}
	}

	va_end(argp);
}