/* triangle.c - triangle classifier
 * spec: https://github.com/regehr/solid_code_class/blob/master/triangle/spec.txt
 * author: David Eisenstat <eisenstatdavid@gmail.com>
 * date: 2014-01-11, revised 2014-01-21
 */

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
  /* number of points */
  COUNT = 3,
  /* number of dimensions */
  DIM = 2,
};

/* maximum coordinate: 2**31 - 1 per the spec
 * MAX must be #defined: enum isn't wide enough,
 * and static const can't go in a typedef
 */
#define MAX ((1ULL << 31) - 1ULL)
/* static assertion */
typedef char overflow_possible[ULLONG_MAX / 2 / DIM / MAX / MAX > 0ULL ? 1 : -1];
/* minimum coordinate: 0 per the spec
 * there is no MIN because this is assumed everywhere
 */

#define SIDE_TYPES \
  X(scalene)       \
  X(isosceles)     \
  X(equilateral)

#define ANGLE_TYPES \
  X(acute)          \
  X(right)          \
  X(obtuse)

#define X(type) type,
enum side_type {
  SIDE_TYPES
};

enum angle_type {
  ANGLE_TYPES
};
#undef X

#define X(type) #type,
static char const *const g_side_type_name[] = {
  SIDE_TYPES
};

static char const *const g_angle_type_name[] = {
  ANGLE_TYPES
};
#undef X

/* s is a null-terminated string
 * returns whether s is matched by ^[0-9]+$
 */
static bool is_decimal_integer(char const *s) {
  do {
    if (!isdigit(*s)) return false;
    s++;
  } while (*s != '\x00');
  return true;
}

/* s is NULL or a null-terminated string
 * returns whether
 * 1. s is not NULL, and
 * 2. s is matched by ^[0-9]+$, and
 * 3. the decimal integer value of s is at most MAX
 * if so, returns in *xptr the value of s
 * if not, preserves *xptr
 * doesn't preserve errno
 */
static bool string_to_coordinate(char const *s, unsigned long long xptr[static 1]) {
  if (s == (char const *)NULL || !is_decimal_integer(s)) return false;
  errno = 0;
  unsigned long long x = strtoull(s, (char **)NULL, 10);
  if (errno != 0 || x > MAX) return false;
  *xptr = x;
  return true;
}

static bool is_not_a_triangle(unsigned long long x[static 3][2]) {
  /* is the signed area zero? */
  return (x[1][0] - x[0][0]) * (x[2][1] - x[1][1]) \
    == (x[1][1] - x[0][1]) * (x[2][0] - x[1][0]);
}

static unsigned long long square(unsigned long long d) {
  return d * d;
}

static unsigned long long distance_squared(unsigned long long const x0[static DIM],
                                           unsigned long long const x1[static DIM]) {
  unsigned long long d2 = 0ULL;
  for (int j = 0; j < DIM; j++) d2 += square(x1[j] - x0[j]);
  return d2;
}

static int compare_unsigned_long_longs(void const *aptr, void const *bptr) {
  unsigned long long a = *(unsigned long long const *)aptr;
  unsigned long long b = *(unsigned long long const *)bptr;
  if (a > b) {
    return 1;
  } else if (a == b) {
    return 0;
  } else {
    return -1;
  }
}

static void sorted_side_lengths_squared(unsigned long long x[static COUNT][DIM],
                                        unsigned long long d2[static COUNT]) {
  for (int i = 0; i < COUNT; i++) d2[i] = distance_squared(x[i], x[(i + 1) % COUNT]);
  qsort(d2, (size_t)COUNT, sizeof *d2, compare_unsigned_long_longs);
}

/* d2 is a sorted array of side lengths squared */
static enum side_type classify_side(unsigned long long const d2[static 3]) {
  if (d2[0] == d2[1]) {
    return d2[1] == d2[2] ? equilateral : isosceles;
  } else {
    return d2[1] == d2[2] ? isosceles : scalene;
  }
}

/* d2 is a sorted array of side lengths squared */
static enum angle_type classify_angle(unsigned long long const d2[static 3]) {
  /* EWD 975 */
  unsigned long long a = d2[0] + d2[1];
  unsigned long long b = d2[2];
  if (a < b) {
    return obtuse;
  } else if (a == b) {
    return right;
  } else {
    return acute;
  }
}

int main(int __attribute__((unused)) argc, char *const *argv) {
  /* consume the program name */
  argv++;
  /* consume and convert the coordinates */
  unsigned long long x[COUNT][DIM];
  for (int i = 0; i < COUNT; i++) {
    for (int j = 0; j < DIM; j++) {
      if (!string_to_coordinate(*argv, &x[i][j])) return EXIT_FAILURE;
      argv++;
    }
  }
  /* have all program parameters been consumed? */
  if (*argv != (char *)NULL) return EXIT_FAILURE;

  if (is_not_a_triangle(x)) {
    printf("not a triangle\n");
  } else {
    unsigned long long d2[COUNT];
    sorted_side_lengths_squared(x, d2);
    printf("%s %s\n",
           g_side_type_name[classify_side(d2)], g_angle_type_name[classify_angle(d2)]);
  }
  return EXIT_SUCCESS;
}
