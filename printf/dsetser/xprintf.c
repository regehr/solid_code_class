#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

/* Converts a long long to a string, either base 10 or 16 */
char* itoa(long long n, char str[], int base) 
{
  if(base == 10)
    sprintf(str, "%lld", n);
  if(base == 16)
    sprintf(str, "%llx", (unsigned long long)n);
  return str;
}

/* Returns the properly padded string */
char* pad(char* str, int field_width, char padding)
{
  int difference = field_width - strlen(str);
  if(field_width == 0 || difference < 0)
    return str;
  for(int i = (strlen(str)+difference); i >= difference; i--)
    str[i] = str[i-difference];
  for(int i = 0; i < difference; i++)
    str[i] = padding;
  return str;
}

/* Returns whether the given character is a valid flag character */
int is_flag(char c)
{
  char* flags = "dsucxn%";
  for(int i = 0; i < strlen(flags); i++)
    if(c == flags[i])
      return 1;
  return 0;
}

/* Handles a printf flag. Returns the number of chars printed */
int handle_flag(char** current_char, va_list args, int chars_printed)
{ 
  char* to_print;
  char buf[256] = {0};
  int printed = 0;
  int field_width = 0;
  char padding = ' ';
  (*current_char)++;
  if(!is_flag(**current_char))
  {
    if(**current_char == '0')  /* Handle 0 flag */
    {
      (*current_char)++;
      padding = '0';
    }
    char dig[10];
    int i = 0;
    if(!is_flag(**current_char)) /* Handle width */
    {
      while(!is_flag(**current_char))
      {
        dig[i++] = **current_char;
        (*current_char)++;
      }
      field_width = atoi(dig);
    }
  }
  switch(**current_char)
  {
    case 'd':
      to_print = pad(itoa(va_arg(args, int), buf, 10), field_width, padding);
      printed += strlen(to_print);
      fputs(to_print, stdout);
      break;
    case 's':
      to_print = va_arg(args, char*);
      printed += strlen(to_print);
      fputs(to_print, stdout);
      break;
    case 'u':
      to_print = pad(itoa(va_arg(args, unsigned int), buf, 10), field_width, padding);
      printed += strlen(to_print);
      fputs(to_print, stdout);
      break;
    case 'c':
      putchar(va_arg(args, int));
      printed++;
      break;
    case 'x':
      to_print = pad(itoa(va_arg(args, int), buf, 16), field_width, padding);
      printed += strlen(to_print);
      fputs(to_print, stdout);
      break;
    case '%':
      putchar('%');
      printed++;
      break;
    case 'n':
      *(va_arg(args, int*)) = printed + chars_printed;
      break;
  }
  return printed;
}

/* My implementation of printf */
int xprintf(char* format, ...)
{
  char* current_char;
  va_list args;
  int chars_printed = 0;
  
  va_start(args, format); 
 
  for(current_char = format; *current_char != '\0'; current_char++)
  {
    if(*current_char == '%')
    {
      chars_printed += handle_flag(&current_char, args, chars_printed);
    }
    else
    {
      putchar(*current_char);
      chars_printed++;
    }
  }
  va_end(args);
  return chars_printed;
}
