#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//https://github.com/synthetos/ICEtest/blob/master/HW/arduino/itoa.c
/* itoa:  convert n to characters in s */
char* itoa(int value, char *string, int radix )
{
  char tmp[33];
  char *tp = tmp;
  long i;
  unsigned long v;
  int sign;
  char *sp;

  if ( string == NULL )
  {
    return 0 ;
  }

  if (radix > 36 || radix <= 1)
  {
    return 0 ;
  }

  sign = (radix == 10 && value < 0);
  if (sign)
  {
    v = -value;
  }
  else
  {
    v = (unsigned long)value;
  }

  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  sp = string;

  if (sign)
    *sp++ = '-';
  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;

  return string;
}
//from http://en.wikibooks.org/wiki/C_Programming/C_Reference/stdlib.h/itoa, thanks :)
/* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

void xprintf(const char *fmt, ...)
{
  const char *p;
  va_list argp;
  int i;
  char *s;
  char fmtbuf[256];
  int * n;
  int total_bytes = 0;

va_start(argp, fmt);

for(p = fmt; *p != '\0'; p++)
	{	
	if(*p != '%')
		{
		putchar(*p);
		total_bytes++;
		continue;
		}

	switch(*++p)
		{
		case 'c':
			i = va_arg(argp, int);
			putchar(i);
			total_bytes++;
			break;

		case 'd':
			i = va_arg(argp, int);
			s = itoa(i, fmtbuf, 10);
			fputs(s, stdout);
			total_bytes++;
			break;

		case 's':
			s = va_arg(argp, char *);
			fputs(s, stdout);
			total_bytes++;
			break;

		case 'x':
			i = va_arg(argp, int);
			s = itoa(i, fmtbuf, 16);
			fputs(s, stdout);
			total_bytes++;
			break;

		case '%':
			putchar('%');
			break;

		case 'u':
			i = va_arg(argp, int);
			s = itoa(i, fmtbuf, 16);
			fputs(s, stdout);
			total_bytes++;
			break;

		case 'n':
			n = va_arg(argp, int *);
			break;
		  
		}
	}

va_end(argp);
return;
}

int main() {
	xprintf("%c\n", 'c');
	xprintf("%d\n", 50);
	xprintf("%s\n", "string");
	xprintf("%x\n", 50);
	xprintf("%%\n");
	return 0;
}
