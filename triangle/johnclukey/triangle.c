/* Triangle Analyzer
 * 
 * Student: John Clukey
 * Date: January 8, 2014
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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
    pts[i] = strtoll(argv[i+1], NULL, 0);
  }
  
  pts[4] = pts[4] - pts[0];
  pts[5] = pts[5] - pts[1];
  pts[2] = pts[2] - pts[0];
  pts[3] = pts[3] - pts[1];
  pts[0] = pts[4] - pts[2];
  pts[1] = pts[5] - pts[3];
  
  l1sq = (pts[0] * pts[0]) + (pts[1] * pts[1]);
  l2sq = (pts[2] * pts[2]) + (pts[3] * pts[3]);
  l3sq = (pts[4] * pts[4]) + (pts[5] * pts[5]);

  if (l1sq == l2sq && l2sq == l3sq) {
    printf("equilateral ");
  }
  else if (l1sq == l2sq || l1sq == l3sq || l2sq == l3sq) {
    printf("isosceles ");
  }
  else {
    printf ("scalene ");
  }
  
  for (i = 0; i < 6; i++) {
    printf("%lld\n", pts[i]);
  }
  
  return 0;
}
