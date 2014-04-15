#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

char *itoa(int value, char *dest) 
{
  int i, v, sign = 0;
  char buf[256];
  char *b = buf;
  char *d = dest;
  
  if (value < 0)
    {
      sign = 1;
      v = -value;
    }
  else 
    {
      v = value;
    }

  while (v && b != buf + 256) {
    i = v % 10;
    v = v / 10;
    *b++ = i + '0';
  }
  if (sign)
    *d++ = '-';
  while (b != buf) 
    {
      *d++ = *--b;
    }
  d = '\0';
  return dest;
}

char *utoa(int value, char *dest, int base) 
{
  int i, v, sign = 0;
  char buf[256];
  char *b = buf;
  char *d = dest;

  while (value && b != buf + 256) {
    i = value % base;
    value = value / base;
    if (i < 10)
      *b++ = i + '0';
    else
      *b++ = i + 'a' - 10;
    
  }
  while (b != buf) 
    {
      *d++ = *--b;
    }
  d = '\0';
  return dest;
}

const char *find_case(const char *p)
{
  for (; *p != '\0'; p++)
    {
      switch (*p)
	{
	case 'd':
	case 'x':
	case 'u':
	case 's':
	case 'n':
	case 'c':
	case '%':
	  return p;
	default:
	  break;
	}
    }
  return p;
}

char *pad_string(char *dest, char *src, int width, char p, char conv)
{
  int i;
  int len = strlen(src);
  width -= len;
  i = 0;
  if (conv == 'd' && *src == '-' && p == '0')
    {
      dest[i++] = *src++;
      width++;
    }
  for (; i < width; i++)
    {
      dest[i] = p;
    }
  strcpy(&dest[i], src);
  return dest;
}

int xprintf(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  const char *p;
  int i, j, *n;
  unsigned int u;
  int char_count = 0;
  char fmtbuf[256];
  char padbuf[256];
  for(p = fmt; *p != '\0'; p++)
    {
      int width;
      char *s;
      const char *c;
      char pad = ' ';
      width = 0;
      if(*p != '%')
	{
	  putchar(*p);
	  char_count++;
	  continue;
	}
      if (*(p+1) == '0') 
	{
	  pad = '0';
	  p++;
	}
      c = find_case(++p);
      j = c - p;
      if (j) 
	{
	  strncpy(fmtbuf, p, j);
	  p += j;
	  fmtbuf[j] = '\0';
	  width = atoi(fmtbuf);
	}
      switch(*p)
	{
	case 'c':
	  i = va_arg(ap, int);
	  for (; width > 1; width--)
	    {
	      putchar(pad);
	      char_count++;
	    }
	  putchar(i);
	  char_count++;
	  break;
	case 'd':
	  i = va_arg (ap, int);
	  s = itoa(i, fmtbuf);
	  s = pad_string(padbuf, s, width, pad, 'd');
	  fputs(s, stdout);
	  char_count += strlen(s);
	  break;
	case 's':
	  s = va_arg(ap, char *);
	  s = pad_string(padbuf, s, width, pad, 's');
	  fputs(s, stdout);
	  char_count += strlen(s);
	  break;
	case 'x':
	  u = va_arg(ap, unsigned int);
	  s = utoa(u, fmtbuf, 16);
	  s = pad_string(padbuf, s, width, pad, 'x');
	  fputs(s, stdout);
	  char_count += strlen(s);
	  break;
	case 'u':
	  u = va_arg(ap, unsigned int);
	  s = utoa(u, fmtbuf, 10);
	  s = pad_string(padbuf, s, width, pad, 'u');
	  fputs(s, stdout);
	  char_count += strlen(s);
	  break;
	case 'n':
	  n = va_arg(ap, int *);
	  *n = char_count;
	  break;
	case '%':
	  putchar('%');
	  char_count++;
	  break;
	}
    }
  va_end(ap);
  return char_count;
}
