/* Triangle Analyzer
 * 
 * Student: John Clukey
 * Date: January 8-13, 2014
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

long long length_squared(long long x, long long y);
const char *side_type_squares(long long asq, long long bsq, long long csq);
const char *angle_from_squares(long long asq, long long bsq, long long csq);

int main (int argc, char **argv) {

  /* Long longs can represent all length values since each coordinate is
   * less than or equal to 2^31-1, so the sum of two squares is less than
   * or equal to 2^63-2^33+2 which is less than 2^63-1, i.e. the square of
   * the euclidean distance can fit in a long long.
   */
  long long pts[6];
  long long l1sq, l2sq, l3sq;
  int i;

  if (argc < 7) {
    printf("Please enter three integral points in first quadrant of the xy-plane.\n");
    return 0;
  }
  
  for (i = 0; i < 6; i++) {
    if (sscanf(argv[i+1], "%lld", &pts[i]) != 1) {
      printf("input error\n");
      return 0;
    }
  }
  
  /* Translating the triangle so that (x_1, y_1) is at the origin
   * and preparing to find the length of the third side.
   */
  pts[4] = pts[4] - pts[0];
  pts[5] = pts[5] - pts[1];
  pts[2] = pts[2] - pts[0];
  pts[3] = pts[3] - pts[1];
  pts[0] = pts[4] - pts[2];
  pts[1] = pts[5] - pts[3];
  
  /* If the ratio between the translated x_2 and x_3 is the same as 
   * the ratio between the translated y_2 and y_3, then all three 
   * points lie along a line or are colocated.
   */
  if (pts[2] * pts[5] == pts[4] * pts[3]) {
    printf("not a triangle\n");
    return 0;
  }
  
  l1sq = length_squared(pts[0], pts[1]);
  l2sq = length_squared(pts[2], pts[3]);
  l3sq = length_squared(pts[4], pts[5]);

  printf("%s ", side_type_squares(l1sq, l2sq, l3sq));
	 
  if (l1sq >= l2sq && l1sq >= l3sq) {
    printf("%s\n", angle_from_squares(l2sq, l3sq, l1sq));
  }
  else if (l2sq >= l1sq && l2sq >= l3sq) {
    printf("%s\n", angle_from_squares(l1sq, l3sq, l2sq));
  }
  else {
    printf("%s\n", angle_from_squares(l1sq, l2sq, l3sq));
  }
  return 0;
}

/* x and y must be no larger than 2^31-1. Return value will be no larger
 * than 2^63-2^33+2.
 */
long long length_squared(long long x, long long y) {
  return x * x + y * y;
}

/* Squares should not be larger than 2^63-2^33+2. */
const char *side_type_squares(long long asq, long long bsq, long long csq) {
  
  /* Equilateral triangles are actually impossible in a two dimensial space 
   * with only integer valued coordinates.
   */
  /*if (asq == bsq && asq == csq) {
    return "equilateral";
  }
  else*/ if (asq == bsq || asq == csq || bsq == csq) {
    return "isosceles";
  }
  else {
    return "scalene";
  }
}

/* Largest squared side should be the third `csq' argument. */
const char *angle_from_squares(long long asq, long long bsq, long long csq) {

  long long diff = csq - asq - bsq;

  /* Law of cosines. */
  if (diff > 0) {
    return "obtuse";
  }
  else if (diff == 0) {
    return "right";
  }
  else {
    return "acute";
  }
}
