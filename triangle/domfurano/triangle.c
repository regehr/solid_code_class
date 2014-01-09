/*
 * Dominic Furano
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define _USE_MATH_DEFINES

double distance(double x0, double y0, double x1, double y1)
{
   return sqrt(pow(x1 - x0, 2.0) + pow(y1 - y0, 2.0));
}

int main(int argc, char *argv[])
{
   double coords[6]; /* Array to hold coordinate values. */
   double A, B, C; /* Length of sides. */
   double a, b, c; /* Magnitude of angles. */
   int i; /* Iteration variable. */

   /* Convert and save command line parameters. */
   for (i = 0; i < argc - 1; i++)
      coords[i] = atof(argv[i + 1]);

   /* Compute length of sides of triangle. */
   A = distance(coords[0], coords[1], coords[2], coords[3]);
   B = distance(coords[2], coords[3], coords[4], coords[5]);
   C = distance(coords[4], coords[5], coords[0], coords[1]);

   /* Compute angles (in radians) between sides using the law of cosines. */
   a = acos( ( pow(B, 2.0) + pow(C, 2.0) - pow(A, 2.0) ) / (2*B*C) );
   b = acos( ( pow(C, 2.0) + pow(A, 2.0) - pow(B, 2.0) ) / (2*C*A) );
   c = acos( ( pow(A, 2.0) + pow(B, 2.0) - pow(C, 2.0) ) / (2*A*B) );

   /* If any of the lengths or angles are 0, then the points don't form a triangle. */
   if (A == 0 || B == 0 || C == 0 || a == 0 || b == 0 || c == 0)
   {
      printf("not a triangle\n");
      exit(EXIT_FAILURE);
   }

   if ( (A == B == C) && (a == b == c) )
      printf("equilateral ");
   else if ( ( (A == B) || (A == C) || (B == C) ) && ( (a == b) || (a == c) || (b == c) ) )
      printf("isosceles ");
   else if ( ( (A != B) && (A != C) && (B != C) ) && ( (a != b) && (a != c) && (b != c) ) )
      printf("scalene ");
   else
      printf("ERROR_1 ");

   if (a == M_PI_2 || b == M_PI_2 || c == M_PI_2)
      printf("right\n");
   else if (a > M_PI_2 || b > M_PI_2 || c > M_PI_2)
      printf("obtuse\n");
   else if (a < M_PI_2 && b < M_PI_2 && c < M_PI_2)
      printf("acute\n");
   else
      printf("ERROR_2\n");

   exit(EXIT_SUCCESS);      
}
