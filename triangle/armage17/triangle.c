/*
 CS5959 Hutch Jorgensen
 1/9/14
 */
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

#define PI 3.14159265

static double findLength(int x1, int y1, int x2, int y2)
{
  // Variables
  int dx = x2 - x1;
  int dy = y2 - y1;

  return sqrt(((double) dx * dx) + ((double) dy * dy));
}

static double findAngle(double angleOp, double s1, double s2)
{
  // Variables
  double takeArcCos = (s1*s1 + s2*s2 - angleOp*angleOp) / (2*s1*s2);
    
  return acos(takeArcCos) * 180.0 / PI;
}

static void longestAngle(double longest, double a1, double a2)
{
  char* type = "scalene";
  char* angle = "acute";

  printf("longest: %.10f\n", longest);
  if(fabs(longest - 90.0) < 0.000001) // Longest angle is 90 degress
      angle = "right";
  else if(longest > 90.0)
      angle = "obtuse";

  // Check if other angles are the same, otherwise leave as scalene. Equilateral not possible with integer
  // points, so I won't check for that case.
  if(a1 == a2) { type = "isosceles"; }

  printf("%s %s\n", type, angle);
}

int main (int argc, char **argv)
{
  // Variables
  int i, xdiff1, xdiff2, ydiff1, ydiff2;
  int nat = 0;
  int xVals[3] = {0};
  int yVals[3] = {0};
  double l01, l12, l02;
  double aA, aB, aC;

  // Parse out the needed values
  for(i = 1; i < 7; i += 2)
    {
      xVals[i/2] = atoi(argv[i]);
      yVals[i/2] = atoi(argv[i+1]);
    }

  // Determine if points are collinear
  xdiff1 = xVals[0] - xVals[1];
  xdiff2 = xVals[1] - xVals[2];
  ydiff1 = yVals[0] - yVals[1];
  ydiff2 = yVals[1] - yVals[2];
  if(xdiff1 == 0 || xdiff2 == 0 || ydiff1 == 0 || ydiff2 == 0) // Make sure that a divide by zero won't be performed, and some boundary checking
    {
      if(xdiff1 == 0 && xdiff2 == 0) // All points on same vertical line, collinear
	nat = 1;
      else if(ydiff1 == 0 && ydiff2 == 0) // All points on same horizontal line
	nat = 1;
      else if((xVals[0] == xVals[1]) && (yVals[0] == yVals[1]) ||
	      (xVals[1] == xVals[2]) && (yVals[1] == yVals[2]) ||
	      (xVals[0] == xVals[2]) && (yVals[0] == yVals[2])) // If any two points are the same, not a triangle
	nat = 1;
    }
  else
    {
      if( fabs(((double) ydiff1 / xdiff1) - // Slope between first two points
	       ((double) ydiff2 / xdiff2)) < .0000000000000001) // See if the distance between the slopes is essentially the same, collinear
	nat = 1;
    }

  // Check if any collinear situation was found and print "not a triangle" if so
  if(nat)
    {
      printf("not a triangle\n");
      return(0);
    }

  // Determine the lengths and angles of the formed triangle
  l01 = findLength(xVals[0], yVals[0], xVals[1], yVals[1]);
  l12 = findLength(xVals[1], yVals[1], xVals[2], yVals[2]);
  l02 = findLength(xVals[0], yVals[0], xVals[2], yVals[2]);

  aA = findAngle(l12, l01, l02);
  aB = findAngle(l02, l01, l12);
  aC = findAngle(l01, l12, l02);

  printf("l01: %f l12: %f l02: %f aA: %f aB: %f aC: %f\n", l01, l12, l02, aA, aB, aC);

  // Check if any one length is greater than the others, this will equate to the largest opposite angle
  if(l01 > l12 && l01 > l02)
      longestAngle(aC, aA, aB);
  else if(l12 > l01 && l12 > l02)
    longestAngle(aA, aB, aC);
  else if(l02 > l01 && l02 > l12)
    longestAngle(aB, aA, aC);
  // The longest length covers almost all triangles, but the only time all the above conditions will be
  // false is two lengths are the same. We can't have equilateral triangles, so this leaves isosceles acute
  else
      printf("%s %s\n", "isosceles", "acute");

  return(0);
  /*int i;

  printf("Number of args: %d\n", argc);
  printf("Size of INT_MAX: %d\n", INT_MAX);

  for (i = 0; i < argc; ++i)
    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
  */
}
