#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void xprintf(const char *, ...);
char * printSpecialCase(va_list, char *, const char *);
int getArgs(int *, char *);
char * pad(bool *, int *, char *);
char *utoa(unsigned int, char*);
char *itoa(int, char *, int);

int main (int argc, char** argv)
{
  int *chars = malloc(sizeof(int));
  xprintf("this%n\n", chars);
  xprintf("%d\n", *chars);
  xprintf("%c\n", 'b');
  xprintf("%d\n", 5);
  xprintf("%d\n", *chars);
  xprintf("%s\n", "string test");
  xprintf("%u\n", (unsigned int)3000000000);
  xprintf("%x\n", 10);

  free(chars);

  return 0;
}

//takes in the format string and any other stuff we need
void xprintf(const char *fmt, ...)
{
  
  //stores each character in the string
  char *p;

  //holds the list of extra args
  va_list argp;

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
      p = printSpecialCase(argp, p, fmt);
    }
  va_end(argp);
}

char * printSpecialCase(va_list argp, char *p, const char *fmt)
{
  //list of stuff to put in format places
  
  int i;
  unsigned int u;
  int *soFar;
  char *s;
  char fmtbuf[256];
  bool padWithZeros = false;
  int width = 0;
  
  while(true)
    {
      switch(*++p)
	{
	  //print the character
	case 'c':
	  i = va_arg(argp, int);
	  putchar(i);
	  return p;
	  
	  //print a number
	case 'd':
	  i = va_arg(argp, int);
	  s = itoa(i, fmtbuf, 10);
	  s = pad(&padWithZeros, &width, s);
	  fputs(s, stdout);
	  return p;
	  
	  //stash the number of characters printed so far
	case 'n':
	  soFar = va_arg(argp, int*);
	  *soFar = p-fmt-1;  //minus one because we don't count this character
	  return p;
	  
	  //print a string
	case 's':
	  s = va_arg(argp, char *);
	  fputs(s, stdout);
	  return p;
	  
	  //print an unsigned int
	case 'u':
	  u = va_arg(argp, unsigned int);
	  s = utoa(u, fmtbuf);
	  s = pad(&padWithZeros, &width, s);
	  fputs(s, stdout);
	  return p;
	  
	  //print the int in hex
	case 'x':
	  i = va_arg(argp, int);
	  s = itoa(i, fmtbuf, 16);
	  s = pad(&padWithZeros, &width, s);
	  fputs(s, stdout);
	  return p;
	  
	  //print a percent sign
	case '%':
	  putchar('%');
	  return p;
	  
	  //get the special cases
	default:
	  
	  //check to see if we want to pad with zeros
	  if(*p == '0')
	    {
	      padWithZeros = true;
	      p++;
	    }
	  
	  //process all of the extra args
	  p += getArgs(&width, p);
	  break;
	}  
    }
}

int getArgs(int * width, char *p)
{      
  //see how many extra things to print out
  *width += atoi(p);
  
  if(*width == 0)
    return 0;
  else
    return (int) floor(log10(abs(*width)));
}

char * pad(bool *padWithZeros, int *width, char *s)
{
  //check to see if the number is negative
  if(*s == '-')
    {
      putchar(*s);
      s++;
      *width -= 1;
    }
  
  int padding;  //loop index
  //if we're padding with zeros
  if(*padWithZeros)
    {
      //print out the appropriate number of zeros
      for(padding = 1; padding < *width; padding++)
	  putchar('0');
    }
  //if we're padding with spaces
  else
    {
      //print out the appropriate number of spaces
      for(padding = 1; padding < *width; padding++)
	putchar(' ');
    }

  //reset the stuff
  *padWithZeros = false;
  *width = 0;

  //return the updated version (no - sign)
  return s;
}

/* converts an unsigned int into a string */
char *utoa(unsigned int toConvert, char* buf)
{
  sprintf(buf, "%u", toConvert);
  return buf;
}

/* A utility function to reverse a string  */
/* Grabbed this from http://www.geeksforgeeks.org/implement-itoa/ */
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
/* Grabbed this from http://www.geeksforgeeks.org/implement-itoa/ */
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
  if (isNegative);
      str[i++] = '-';
  
  str[i] = '\0'; // Append string terminator
  
  // Reverse the string
  reverse(str, i);
  
  return str;
}
