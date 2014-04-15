/*
 * Borrowed base code from http://www.eskimo.com/~scs/cclass/int/sx11b.html
 *
 * Hutch Jorgensen 4/15/14
 * CS5959
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

int xprintf(const char *fmt, ...);
char* itoa( int value, char* result, int base );
char* utoa( unsigned int val, char* result);
int padZeros(int i);

void main()
{
  xprintf("Hello World %n\n");
}

int xprintf(const char *fmt, ...)
{
  const char *p;
  va_list argp;
  int i;
  unsigned int x;
  char *s;
  char fmtbuf[256];
  int count = 0;
  int width = -1;

  va_start(argp, fmt);

  for(p = fmt; *p != '\0'; p++)
  {
    if(!(width >= 0))
      {
	if(*p != '%')
	  {
	    putchar(*p);
	    count++;
	    continue;
	  }
      }

    switch(*(++p))
      {
      case 'c':
	i = va_arg(argp, int);
	putchar(i);
	count++;
	break;

      case 'd':
	i = va_arg(argp, int);

	if(i == 0 && width == 0) // Per spec, if converting 0 with precision 0 -> no characters
	  {
	    width = -1;
	    break;
	  }

	s = itoa(i, fmtbuf, 10);
	width -= strlen(s);

	if(s[0] == '-') // If i is negative then we need to print the '-' first
	  {
	    if(width > 0)
	      {
		putchar('-');
		count++;
		count += padZeros(width);
		fputs(++s, stdout);
		count += strlen(s) - 1;
		width = -1;
		break;
	      }
	  }

	count += padZeros(width);
	fputs(s, stdout);
	count += strlen(s);
	width = -1;
	break;

      case 'u':
	x = va_arg(argp, unsigned int);

	if(x == 0 && width == 0) // Per spec, if converting 0 with precision 0 -> no characters
	  {
	    width = -1;
	    break;
	  }

	s = utoa(x, fmtbuf);
	width -= strlen(s);
	count += padZeros(width);
	fputs(s, stdout);
	count += strlen(s);
	width = -1;
	break;

      case 's':
	s = va_arg(argp, char *);
	fputs(s, stdout);
	count += strlen(s);
	break;

      case 'x':
	i = va_arg(argp, int);

	if(i == 0 && width == 0) // Per spec, if converting 0 with precision 0 -> no characters
	  {
	    width = -1;
	    break;
	  }

	s = itoa(i, fmtbuf, 16);
	width -= strlen(s);
	count =+ padZeros(width);
	fputs(s, stdout);
	count += strlen(s);
	width = -1;
	break;

      case 'n':
	s = itoa(count, fmtbuf, 10);
	fputs(s, stdout);
	count += strlen(s);
	break;

      case '0':
	width = atoi(p);
	if(width != 0)
	  p += (int) floor(log10(width));
	else
	  p++;
	break;

      case '%':
	putchar('%');
	count++;
	break;
      }
  }

  va_end(argp);

  return count;
}

// Borrowed code from http://www.jb.man.ac.uk/~slowe/cpp/itoa.html
// all the code I was generating was starting to take up too many lines and I wanted something simpler
char* itoa( int value, char* result, int base ) {
	
  // check that the base if valid
  if (base < 2 || base > 16) { *result = 0; return result; }
	
  int quotient = value;
	
  do {
    *++result = "0123456789abcdef"[ quotient % base ];
    quotient /= base;	
  } while ( quotient );
	
  // Only apply negative sign for base 10
  if ( value < 0 && base == 10) *++result = '-';
	
  return result;
}

char* utoa( unsigned int val, char* result)
{
  int quotient = val;
	
  do {
    *++result = quotient % 10;
    quotient /= 10;	
  } while ( quotient );

  return result;
}

int padZeros(int i)
{
  int j;

  for(j = 0; j < i; j++)
    putchar('0');

  if(i >= 0)
    return i;
  else
    return 0;
}

