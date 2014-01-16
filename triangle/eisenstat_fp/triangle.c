/* triangle-float.c: triangle classifier via floating-point arithmetic
 * author: David Eisenstat <eisenstatdavid@gmail.com>
 * date: 2014-01-13
 */

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#if 0
static long double FabsCarg(long double complex z) {
  return fabsl(cargl(z));
}
#else
/* same order properties, less trig! */
static long double FabsCarg(long double complex z) {
  long double x = creall(z);
  long double y = cimagl(z);
  /* must test to avoid 0/0 => NaN */
  return copysignl(y != 0 ? x / y : INFINITY, -x);
}
#endif

static long double Angle(long double complex a,
                         long double complex b,
                         long double complex c) {
  return FabsCarg((a - b) * conjl(c - b));
}

static void Sort(long double *alpha, long double *beta) {
  if (*alpha > *beta) {
    long double gamma = *alpha;
    *alpha = *beta;
    *beta = gamma;
  }
}

int main(int argc, char *const *argv) {
  long double complex a = strtold(argv[1], (char **)NULL) \
    + strtold(argv[2], (char **)NULL) * I;
  long double complex b = strtold(argv[3], (char **)NULL) \
    + strtold(argv[4], (char **)NULL) * I;
  long double complex c = strtold(argv[5], (char **)NULL) \
    + strtold(argv[6], (char **)NULL) * I;
  long double alpha = Angle(c, a, b);
  long double beta = Angle(a, b, c);
  long double gamma = Angle(b, c, a);
  Sort(&alpha, &beta);
  Sort(&beta, &gamma);
  Sort(&alpha, &beta);
  long double zero = FabsCarg(1);
  long double pi = FabsCarg(-1);
  if (alpha == zero || gamma == pi) {
    printf("not a triangle\n");
  } else {
    static char const *const side_type[] = {
      "scalene",
      "isosceles",
      "equilateral"
    };
    char const *angle_type;
    long double half_pi = FabsCarg(I);
    if (gamma > half_pi) {
      angle_type = "obtuse";
    } else if (gamma == half_pi) {
      angle_type = "right";
    } else {
      angle_type = "acute";
    }
    printf("%s %s\n",
           side_type[(alpha == beta) + (beta == gamma)], angle_type);
  }
}
