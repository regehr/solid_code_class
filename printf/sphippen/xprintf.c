#include "xprintf.h"

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

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
    /* TODO: check these int operations for safety */
    acc *= 10;
    acc += digit;
    cur_fmt++;
    next = *cur_fmt;
  } while (isdigit(next));

  *value = acc;
  *new_fmt = cur_fmt;
  return true;
}

static int print_pad(FILE *stream, int count, bool zero) {
  int total = 0;
  char c = zero ? '0' : ' ';
  for (int i = 0; i < count; i++) {
    int ret = fputc(c, stream);
    if (ret < 0) {
      total = -1;
      break;
    } else {
      total++;
    }
  }
  return total;
}

void reverse_inplace(char *buf, size_t len) {
  size_t half = len / 2;
  for (int i = 0; i < half; i++) {
    char tmp = buf[i];
    buf[i] = buf[len-i-1];
    buf[len-i-1] = tmp;
  }
}

const static char dig_lookup[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

/* Return value only valid before next call to function. */
const char* itostr(int val, int base, size_t *len) {
  assert(base >= 2 && base <= 16 && "Only accepted bases are binary up to hex");

  static char buf[255]; /* should be enough */

  /* Special case */
  if (val == 0) {
    buf[0] = '0';
    buf[1] = '\0';
    return &buf[0];
  }

  bool neg = (val < 0);

  char *cur = &buf[0];
  while (val != 0) {
    int new_dig = val % base;
    if (neg) new_dig *= -1;
    *cur++ = dig_lookup[new_dig];
    val = val / base;
  }

  *cur = '\0';

  reverse_inplace(buf, cur - buf);
  if (neg) {
    memmove(buf+1, buf, strlen(buf));
    buf[0] = '-';
    *len = (cur - buf) + 1;
  } else {
    *len = cur - buf;
  }

  return buf;
}

/* Return value only valid before next call to function. */
const char* utostr(unsigned val, int base, size_t *len) {
  assert(base >= 2 && base <= 16 && "Only accepted bases are binary up to hex");

  static char buf[255]; /* should be enough */

  /* Special case */
  if (val == 0) {
    buf[0] = '0';
    buf[1] = '\0';
    return &buf[0];
  }

  char *cur = &buf[0];
  while (val != 0) {
    int new_dig = val % base;
    *cur++ = dig_lookup[new_dig];
    val = val / base;
  }

  *cur = '\0';

  reverse_inplace(buf, cur - buf);
  *len = cur - buf;
  return buf;
}

int xvfprintf(FILE *stream, const char *fmt, va_list ap) {
  assert(stream != NULL && "Can't print to NULL FILE");
  assert(fmt != NULL && "Can't print from NULL format string");

  int char_count = 0;
  int this_char_count = 0;

  while (*fmt != '\0') {
    if (*fmt == '%') {
      fmt++;
      /* Check for '0' flag */
      bool use_zero = (*fmt == '0');
      if (use_zero)
        fmt++;

      /* Parse out field width */
      int width = -1;
      const char *new_fmt;
      bool has_width = parse_int(fmt, &width, &new_fmt);
      if (has_width)
        fmt = new_fmt;

      switch (*fmt) {
        case 'd': {
          int val = va_arg(ap, int);
          /* TODO: impl */
          break;
        }
        case 's': {
          const char *val = va_arg(ap, const char *);
          size_t val_len = strlen(val);

          if (width > val_len) {
            int res = print_pad(stream, width - val_len, use_zero);
            if (res < 0) {
              this_char_count = -1;
              break;
            } else {
              this_char_count += res;
            }
          }

          int res = fputs(val, stream);
          if (res < 0)
            this_char_count = -1;
          else
            this_char_count += (int)val_len;
          break;
        }
        case 'u': {
          unsigned val = va_arg(ap, unsigned);
          size_t val_len;
          const char *val_str = utostr(val, 10, &val_len);

          if (width > val_len) {
            int res = print_pad(stream, width - val_len, use_zero);
            if (res < 0) {
              this_char_count = -1;
              break;
            } else {
              this_char_count += res;
            }
          }

          int res = fputs(val_str, stream);
          if (res < 0)
            this_char_count = -1;
          else
            this_char_count += (int)val_len;
          break;
        }
        case 'c': {
          int val = va_arg(ap, int);
          int res = fputc(val, stream);
          if (res < 0)
            this_char_count = -1;
          else
            this_char_count += 1;
          break;
        }
        case 'x': {
          unsigned val = va_arg(ap, unsigned);
          size_t val_len;
          const char *val_str = utostr(val, 16, &val_len);

          if (width > val_len) {
            int res = print_pad(stream, width - val_len, use_zero);
            if (res < 0) {
              this_char_count = -1;
              break;
            } else {
              this_char_count += res;
            }
          }

          int res = fputs(val_str, stream);
          if (res < 0)
            this_char_count = -1;
          else
            this_char_count += (int)val_len;
          break;
        }
        case 'n': {
          int *val = va_arg(ap, int *);
          *val = char_count;
          break;
        }
        case '%': {
          int result = fputc((int)'%', stream);
          if (result == EOF)
            this_char_count = -1;
          else
            this_char_count = 1;
          break;
        }
        default: {
          this_char_count = -1;
          break;
        }
      }

    } else {
      int result = fputc((int)*fmt, stream);
      if (result == EOF)
        this_char_count = -1;
      else
        this_char_count = 1;
    }
    
    fmt++;
    /* If there was an output failure */
    if (this_char_count < 0)
      return -1;

    /* If the number of characters printed is too large to fit in an int */
    if (char_count > (INT_MAX - this_char_count))
      return -1;

    char_count += this_char_count;
    this_char_count = 0;
  }

  return char_count;
}

