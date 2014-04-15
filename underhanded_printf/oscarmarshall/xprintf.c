#include <assert.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static long long exponentiate(long long base, long long expt) {
  long long result = 1;
  for (long long i = 0; i < expt; i++) {
    result *= base;
  }
  return result;
}

static char *int_to_string(unsigned int value, int base, bool flag0, int width,
    char *str) {
  while (exponentiate(base, width + 1) <= value) width++;
  bool prefix = true;
  for (; width >= 0; width--) {
    int place = value / exponentiate(base, width);
    value %= exponentiate(base, width);
    if (prefix) {
      if (place == 0 && !flag0) {
        strcat(str, " ");
        continue;
      }
      prefix = false;
    }
    char tmp[2];
    tmp[0] = place + (place < 10 ? '0' : 'a' - 10);
    tmp[1] = 0;
    strcat(str, tmp);
  }
  assert(value == 0);
  return str;
}

void xprintf(const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);

  int bytes_written = 0;
  for (const char *p = fmt; *p != 0; p++) {
    // If it isn't the beginning of a format string, then put the char and
    // continue.
    if (*p != '%') {
      putchar(*p);
      bytes_written += 1;
      continue;
    }
    p++;

    bool flag0 = false;
    if (*p == '0') {
      flag0 = true;
      p++;
    }

    int width = 0;
    while ('0' <= *p && *p <= '9') {
      width *= 10;
      width += *p - '0';
      p++;
    }

    switch(*p) {
      case 'd': {
        int i = va_arg(argp, int);

        if (i < 0) {
          putchar('-');
          bytes_written += 1;
          i *= -1;
        }

        char buf[10] = "";
        fputs(int_to_string(i, 10, flag0, width, buf), stdout);
        bytes_written += strlen(buf);
        break;
      }

      case 'u': {
        unsigned int i = va_arg(argp, unsigned int);

        char buf[10] = "";
        fputs(int_to_string(i, 10, flag0, width, buf), stdout);
        bytes_written += strlen(buf);
        break;
      }

      case 'x': {
        unsigned int i = va_arg(argp, unsigned int);

        char buf[10] = "";
        fputs(int_to_string(i, 16, flag0, width, buf), stdout);
        bytes_written += strlen(buf);
        break;
      }

      case 'c': {
        putchar(va_arg(argp, int));
        bytes_written += 1;
        break;
      }

      case 's': {
        char *s = va_arg(argp, char *);
        fputs(s, stdout);
        bytes_written += strlen(s);
        break;
      }

      case 'n': {
        int *n = va_arg(argp, int *);
        *n = bytes_written;
        break;
      }

      case '%': {
        putchar('%');
        bytes_written += 1;
        break;
      }
    }
  }
  va_end(argp);
}