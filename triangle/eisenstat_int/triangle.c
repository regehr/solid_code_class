/* triangle.c - triangle classifier
 * spec: https://github.com/regehr/solid_code_class/blob/master/triangle/spec.txt
 * author: David Eisenstat <eisenstatdavid@gmail.com>
 * date: 2014-01-11
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* number of points */
#define COUNT (3)
/* number of dimensions */
#define DIM (2)
/* maximum coordinate: 2**31 - 1 per the spec
 * ACHTUNG!  integer overflow is possible if
 *     DIM * MAX * MAX
 * overflows a long long or
 *     2 * DIM * MAX * MAX
 * overflows an unsigned long long
 */
#define MAX (0x7fffffffLL)
/* minimum coordinate: 0 per the spec
 * this is assumed for many purposes
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
static char const *const Side_type_name[] = {
  SIDE_TYPES
};

static char const *const Angle_type_name[] = {
  ANGLE_TYPES
};
#undef X

/* s is NULL or a null-terminated string
 * returns whether
 * 1. s is not NULL, and
 * 2. s is matched by ^[0-9]+$, and
 * 3. the decimal integer value of s is at most MAX
 * if so, returns in *xptr the value of s
 * if not, has no side effects
 */
static bool string_to_coordinate(char const *s, long long *xptr) {
  if (s == (char const *)NULL) return false;
  long long x = 0LL;
  do {
    unsigned int d = (unsigned int)*s - (unsigned int)'0';
    if (d >= 10U) return false;
    x = x * 10LL + (long long)d;
    if (x > MAX) return false;
    s++;
  } while (*s != '\x00');
  *xptr = x;
  return true;
}

static bool is_not_a_triangle(long long x[static 3][2]) {
  /* is the signed area zero? */
  return (x[1][0] - x[0][0]) * (x[2][1] - x[0][1]) == \
    (x[1][1] - x[0][1]) * (x[2][0] - x[0][0]);
}

static long long distance_squared(long long const x0[static DIM],
                                  long long const x1[static DIM]) {
  long long d2 = 0LL;
  for (int j = 0; j < DIM; j++) {
    long long dj = x1[j] - x0[j];
    d2 += dj * dj;
  }
  return d2;
}

static void insert_sorted(long long d2i, int i, long long d2[static i + 1]) {
  for (; i > 0 && d2[i - 1] > d2i; i--) d2[i] = d2[i - 1];
  d2[i] = d2i;
}

static void sorted_side_lengths_squared(long long x[static COUNT][DIM],
                                        long long d2[static COUNT]) {
  for (int i = 0; i < COUNT; i++) {
    insert_sorted(distance_squared(x[i], x[(i + 1) % COUNT]), i, d2);
  }
}

/* d2 is a sorted array of side lengths squared */
static enum side_type classify_side(long long const d2[static 3]) {
  if (d2[0] == d2[1]) {
    return d2[1] == d2[2] ? equilateral : isosceles;
  } else {
    return d2[1] == d2[2] ? isosceles : scalene;
  }
}

/* d2 is a sorted array of side lengths squared */
static enum angle_type classify_angle(long long const d2[static 3]) {
  /* EWD 975 */
  unsigned long long a = (unsigned long long)d2[0] + (unsigned long long)d2[1];
  unsigned long long b = (unsigned long long)d2[2];
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
  long long x[COUNT][DIM];
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
    long long d2[COUNT];
    sorted_side_lengths_squared(x, d2);
    printf("%s %s\n",
           Side_type_name[classify_side(d2)],
           Angle_type_name[classify_angle(d2)]);
  }
  return EXIT_SUCCESS;
}
