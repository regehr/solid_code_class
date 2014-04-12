#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>


char *itoa(int, char *, int);
void xprintf(const char *, ...);

char *utoa(unsigned int toConvert, char* buf)
{
  sprintf(buf, "%u", toConvert);
  return buf;
}

int main (int argc, char** argv)
{
  int *chars;
  unsigned int testInt = 3294967295;
  xprintf("this%n is a test string, %d, %u\n", chars, 5, testInt);
  xprintf("%d\n", *chars);
  printf("this%n is a test string, %d, %u\n", chars, 5, testInt);
  printf("%d\n", *chars);

  return 0;
}

//takes in the format string and any other stuff we need
void xprintf(const char *fmt, ...)
{
  
  //stores each character in the string
  const char *p;

  //list of stuff to put in format places
  va_list argp;
  int i;
  unsigned int u;
  int *soFar;
  char *s;
  char fmtbuf[256];
  
  //start the va_arg stuff
  va_start(argp, fmt);
  
  //for each char in the format string
  for(p = fmt; *p != '\0'; p++)
    {
      //if it's not a format option
      if(*p != '%')
	{
	  //just print it out
	  putchar(*p);
	  continue;
	}
      /*
       * support the following flag:
       * 0
       *
       * also, Josh wants this discussed separately:
       * field width digit string
       */
      switch(*++p)
	{
	case 'c':
	  i = va_arg(argp, int);
	  putchar(i);
	  break;
	  
	  //print a number
	case 'd':
	  i = va_arg(argp, int);
	  s = itoa(i, fmtbuf, 10);
	  fputs(s, stdout);
	  break;
	  
	case 'n':
	  soFar = va_arg(argp, int*);
	  *soFar = p-fmt-1;  //minus one because we don't count this character
	  break;

	  //print a string
	case 's':
	  s = va_arg(argp, char *);
	  fputs(s, stdout);
	  break;
	  
	case 'u':
	  u = va_arg(argp, unsigned int);
	  s = utoa(u, fmtbuf);
	  fputs(s, stdout);
	  break;

	case 'x':
	  i = va_arg(argp, int);
	  s = itoa(i, fmtbuf, 16);
	  fputs(s, stdout);
	  break;
	  
	  //print a percent sign
	case '%':
	  putchar('%');
	  break;
	}
    }
  va_end(argp);
}

/* A utility function to reverse a string  */
void reverse(char str[], int length)
{
  int start = 0;
  int end = length -1;
  while (start < end)
    {
      //stash the first element to swap
      char temp = *(str+start);

      //replace it
      *(str+start) = *(str+end);

      //replace the other one with temp
      *(str+end) = temp;
      start++;
      end--;
    }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
  int i = 0;
  bool isNegative = false;
  
  /* Handle 0 explicitely, otherwise empty string is printed for 0 */
  if (num == 0)
    {
      str[i++] = '0';
      str[i] = '\0';
      return str;
    }
  
  // In standard itoa(), negative numbers are handled only with 
  // base 10. Otherwise numbers are considered unsigned.
  if (num < 0 && base == 10)
    {
      isNegative = true;
      num = -num;
    }
 
  // Process individual digits
  while (num != 0)
    {
      int rem = num % base;
      str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
      num = num/base;
    }
  
  // If number is negative, append '-'
  if (isNegative)
    {
      str[i++] = '-';
    }
  
  str[i] = '\0'; // Append string terminator
  
  // Reverse the string
  reverse(str, i);
  
  return str;
}
