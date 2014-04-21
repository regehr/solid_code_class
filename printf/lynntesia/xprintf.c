#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

extern char *itoa(int, char *, int);
//char *itoa(int, char *, int);

void xprintf(const char *fmt, ...)
{
  const char *p;
  va_list argp;
  int i;
  char *s;
  char fmtbuf[256];
  int *n;

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

		case 'u':
			i = va_arg(argp, int);
			s = itoa(i, fmtbuf, 16);
			fputs(s, stdout);
			break;

		case 'n':
			n = va_arg(argp, int *);
			break;
		  
		}



	}

va_end(argp);
return 0;
}

int main() {
	xprintf("%c\n", 'c');
	xprintf("%d\n", 50);
	xprintf("%s\n", "string");
	xprintf("%x\n", 50);
	xprintf("%%\n");
}
