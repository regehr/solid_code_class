/* File: triangle.c
   Author: Spencer Phippen

   As we all know, you can never trust floating point numbers with exact
   equality tests. There are simple integer algorithms to classify triangles
   based on the vertices, but overflow becomes an issue.

   Two solutions immediately present themselves:
   (1) Use big enough fixed width types.
   (2) Use arbitrary precision types.

   I initially wrote this code in the style of (1), but that leaves it fragile
   to future changes, and the math wasn't detailed in this file.
   It's in the style of (2) now - GMP is pretty neat.
   (but the CADE GMP is borked, so I had to build my own version) */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gmp.h>
#include <stdbool.h>

typedef enum { Equ, Iso, Sca } Side;
typedef enum { Acu, Rig, Obt } Angle;

/* Returns true and sets |side| and |angle| if the given coordinates define a
   non-degenerate triangle.
   Returns false otherwise. */
bool determineTriangle(mpz_t xs[3], mpz_t ys[3], Side* side, Angle* angle);

/* Prints the output for a triangle with the given Side and Angle values. */
void printTri(Side side, Angle angle);

int main(int argc, char* argv[])
{
  if (argc != 7) {
    fputs("Usage: ./triangle x1 y1 x2 y2 x3 y3\n", stderr);
    exit(1);
  }

  /* Read points from cmd line */
  mpz_t xs[3];
  mpz_t ys[3];
  for (int i = 0; i < 3; i++) {
    mpz_init_set_str(xs[i], argv[2*i + 1], 10);
    mpz_init_set_str(ys[i], argv[2*i + 2], 10);
  }

  Side side;
  Angle angle;
  if (determineTriangle(xs, ys, &side, &angle))
    printTri(side, angle);
  else
    puts("not a triangle");

  for (int i = 0; i < 3; i++)
    mpz_clears(xs[i], ys[i], NULL);

  return 0;
}

/* Used for qsort on an mpz_t array. */
int mpzCmp(const void* a, const void* b);
/* Returns the Side value for a triangle with the given squared side lengths. */
Side determineSide(mpz_t sqdLens[3]);
/* Returns the Angle value for a triangle with the given squard side lengths. */
Angle determineAngle(mpz_t sqdLens[3]);

bool determineTriangle(mpz_t xs[3], mpz_t ys[3], Side* side, Angle* angle)
{
  bool toRet;

  /* Calculate x and y deltas between vertices */
  mpz_t xdiffs[3];
  mpz_t ydiffs[3];
  for (int i = 0, j = 2; i < 3; j = i++) {
    mpz_inits(xdiffs[i], ydiffs[i], NULL);
    mpz_sub(xdiffs[i], xs[i], xs[j]);
    mpz_sub(ydiffs[i], ys[i], ys[j]);
  }

  mpz_t tmp1, tmp2, result;
  mpz_inits(tmp1, tmp2, result, NULL);

  /* Determine if the three points are colinear, based on cross product */
  mpz_mul(tmp1, xdiffs[0], ydiffs[1]);
  mpz_mul(tmp2, ydiffs[0], xdiffs[1]);
  mpz_sub(result, tmp1, tmp2);

  if (mpz_cmp_si(result, 0) == 0) {
    toRet = false;
  } else {
    /* Calculate the squared length of each side */
    mpz_t sqdLens[3];
    for (int i = 0; i < 3; i++) {
      mpz_init(sqdLens[i]);

      mpz_mul(tmp1, xdiffs[i], xdiffs[i]);
      mpz_mul(tmp2, ydiffs[i], ydiffs[i]);
      mpz_add(sqdLens[i], tmp1, tmp2);
    }
    /* Sort side lengths for convenience in determining angle properties */
    qsort(sqdLens, sizeof(sqdLens) / sizeof(sqdLens[0]), sizeof(sqdLens[0]), mpzCmp);

    assert(mpz_cmp(sqdLens[0], sqdLens[1]) <= 0 && mpz_cmp(sqdLens[1], sqdLens[2]) <= 0 && "Squared lengths in bad order");

    *side = determineSide(sqdLens);
    *angle = determineAngle(sqdLens);

    for (int i = 0; i < 3; i++)
      mpz_clear(sqdLens[i]);

    toRet = true;
  }

  mpz_clears(tmp1, tmp2, result, NULL);
  for (int i = 0; i < 3; i++)
    mpz_clears(xdiffs[i], ydiffs[i], NULL);

  return toRet;
}

int mpzCmp(const void* a, const void* b)
{
  mpz_t* first = (mpz_t*)a;
  mpz_t* second = (mpz_t*)b;
  return mpz_cmp(*first, *second);
}

Side determineSide(mpz_t sqdLens[3])
{
  if (mpz_cmp(sqdLens[0], sqdLens[1]) == 0 &&
      mpz_cmp(sqdLens[1], sqdLens[2]) == 0)
    return Equ;
  else if (mpz_cmp(sqdLens[0], sqdLens[1]) == 0 ||
           mpz_cmp(sqdLens[1], sqdLens[2]) == 0 ||
           mpz_cmp(sqdLens[2], sqdLens[0]) == 0)
    return Iso;
  else
    return Sca;
}

Angle determineAngle(mpz_t sqdLens[3])
{
  /* From the law of cosines (where a <= b <= c are the side lengths),
     a^2 + b^2 > c^2 in acute triangles,
     a^2 + b^2 = c^2 in right triangles,
     a^2 + b^2 < c^2 in obtuse triangles */
  Angle toRet;
  mpz_t leftOver;
  mpz_init_set(leftOver, sqdLens[2]);
  mpz_sub(leftOver, leftOver, sqdLens[1]);
  mpz_sub(leftOver, leftOver, sqdLens[0]);

  int cmp = mpz_cmp_si(leftOver, 0);
  if (cmp < 0)
    toRet = Acu;
  else if (cmp == 0)
    toRet = Rig;
  else
    toRet = Obt;

  mpz_clear(leftOver);
  return toRet;
}

void printTri(Side side, Angle angle)
{
  const char* sideStr = NULL;
  switch (side) {
    case Equ:
      sideStr = "equilateral";
      break;
    case Iso:
      sideStr = "isosceles";
      break;
    case Sca:
      sideStr = "scalene";
      break;
    default:
      assert(0 && "bad Side enum value");
      break;
  }
  const char* angleStr = NULL;
  switch (angle) {
    case Acu:
      angleStr = "acute";
      break;
    case Rig:
      angleStr = "right";
      break;
    case Obt:
      angleStr = "obtuse";
      break;
    default:
      assert(0 && "bad Angle enum value");
      break;
  }

  printf("%s %s\n", sideStr, angleStr);
}
