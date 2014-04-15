#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

char *itoa(int value, char * string, int radix)
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

  while (v || tp == tmp);
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

unsigned htoi(char s[])
{
    int i = 0; /* Iterate over s */
    unsigned n = 0; /* Built up number */
 
    while ( s[i] != '\0' )
    {
        unsigned t;
        if ( s[i] >= 'A' && s[i] <= 'F' )
            t = s[i] - 'A' + 10;
        else if ( s[i] >= 'a' && s[i] <= 'f' )
            t = s[i] - 'a' + 10;
        else if ( s[i] >= '0' && s[i] <= '9' )
            t = s[i] - '0';
        else
            return n;
 
        n = 16 * n + t;
        ++i;
    }
 
    return n;
}

char *utoa(unsigned value, char * string, int radix)
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

int bCount(char * s)
{

  int totalBytes = 0;
  int  j = 0;
  while(s[j] != '\0'){
    totalBytes++;
    j++;
  }
  return totalBytes - 1;
  
}

int xprintf(const char *fmt, ...)
{
  const char *p;
  va_list argp;
  int i;
  char *s;
  char fmtbuf[256];
  int totalBytes = -1;
  int * myPointer;

  va_start(argp, fmt);

  for(p = fmt; *p != '\0'; p++)
    {
      totalBytes++;

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
	  
	case 'i':
	case 'd':
	  i = va_arg(argp, int);
	  s = itoa(i, fmtbuf, 10);
	  totalBytes += bCount(s);
	  fputs(s, stdout);
	  break;
	  
	case 's':
	  s = va_arg(argp, char *);
	  totalBytes += bCount(s);
	  fputs(s, stdout);
	  break;
	  
	case 'x':
	  i = va_arg(argp, int);
	  s = itoa(i, fmtbuf, 16);
	  totalBytes += bCount(s);
	  fputs(s, stdout);
	  break;
	  
	case '%':
	  putchar('%');
	  break;
	  
	case 'u':
	  i = va_arg(argp, int);
	  s = itoa(i, fmtbuf,16 );
	  unsigned value  = htoi(s);
	  s = utoa(value, fmtbuf, 10);
	  totalBytes += bCount(s);
	  fputs(s, stdout);
	  break;

	case 'n':
	  myPointer = va_arg(argp, int *);
	  *myPointer = totalBytes;
	  break;
	  
	}


    }

  va_end(argp);
  return totalBytes;
}

int main()
{
  xprintf("String Test should be Hello: %s\n", "Hello");
  xprintf("Double Test should be 10: %d\n", 10);
  xprintf("Unsigned Positive Test should be 3: %u\n", 3);
  xprintf("Negative Unsigned Test should be 4294967292: %u\n", -3);
  xprintf("Percent Test: %%\n");
  xprintf("Char Test should be t: %c\n", 't');
  xprintf("Hex Test should be f: %x\n", 15);

  
 
  return 0;

}
