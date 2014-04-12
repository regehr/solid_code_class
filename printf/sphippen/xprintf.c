#include "xprintf.h"

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/* The first few are just wrappers around xvfprintf */

int xprintf(const char *fmt, ...) {
  va_list ap;
  int res;

  va_start(ap, fmt);
  res = xvprintf(fmt, ap);
  va_end(ap);

  return res;
}

int xfprintf(FILE *stream, const char *fmt, ...) {
  va_list ap;
  int res;

  va_start(ap, fmt);
  res = xvfprintf(stream, fmt, ap);
  va_end(ap);

  return res;
}

int xvprintf(const char *fmt, va_list ap) {
  return xvfprintf(stdout, fmt, ap);
}

/* The real meat starts here */

/* Only works for positive ints (that's all we need for printf) */
static bool parse_int(const char *fmt, int *value, const char **new_fmt) {
  assert(fmt != NULL && "Can't parse int from NULL string");
  assert(value != NULL && "Can't parse int into NULL int*");
  assert(new_fmt != NULL && "Can't parse int and put after char* into NULL ptr");

  const char *cur_fmt = fmt;
  int acc = 0;

  char next = *cur_fmt;
  if (!isdigit(next))
    return false;

  do {
    int digit = (next - '0');
    /* TODO: check these int operations */
    acc *= 10;
    acc += digit;
    cur_fmt++;
    next = *cur_fmt;
  } while (isdigit(next));

  *value = acc;
  *new_fmt = cur_fmt;
  return true;
}


static int print_fmt(const char *fmt, va_list ap, const char **new_fmt) {
  assert(fmt != NULL && "Can't print from NULL format string");
  assert(*fmt == '%' && "Can't print format from non-format-specifier string");
  assert(new_fmt != NULL && "Invalid new_fmt pointer argument");

  const char *cur_fmt = fmt;
  cur_fmt++; /* Skip over the '%' */

  /* Check for '0' flag */
  bool use_zero = (*cur_fmt == '0');
  if (use_zero)
    cur_fmt++;

  /* Parse out field width */
  int width = -1;
  const char *new_cur_fmt;
  bool has_width = parse_int(cur_fmt, &width, &new_cur_fmt);
  if (has_width)
    cur_fmt = new_cur_fmt;

  /* Check conversion char and print appropriate characters */
  /* TODO: impl here */
  return 0;
}

int xvfprintf(FILE *stream, const char *fmt, va_list ap) {
  assert(stream != NULL && "Can't print to NULL FILE");
  assert(fmt != NULL && "Can't print from NULL format string");

  int char_count = 0;
  int this_char_count = 0;
  const char *new_fmt;

  while (*fmt != '\0') {
    if (*fmt == '%') {
      this_char_count = print_fmt(fmt, ap, &new_fmt);
      fmt = new_fmt;
    } else {
      int result = fputc((int)*fmt, stream);
      fmt++;
      if (result == EOF)
        this_char_count = -1;
      else
        this_char_count = 1;
    }
    
    /* If there was an output failure */
    if (this_char_count < 0)
      return -1;

    /* If the number of characters printed is too large to fit in an int */
    if (char_count > (INT_MAX - this_char_count))
      return -1;

    char_count += this_char_count;
  }

  return nChars;
}

