/*
 * Dominic Furano
 * January 2013
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Returns the dot product of two vectors. If the two vectors are acute,
   the dot product is positive. If the two vectors are obtuse, the dot product
   is negative. If the two vectors are perpendicular, the dot product is zero. */
long long dot_product(long long x0, long long y0, long long x1, long long y1)
{
    return (x0 * x1) + (y0 * y1);
}

/* Returns the sqd_dst between two vectors. */
long long sqd_dst(long long x0, long long y0, long long x1, long long y1)
{
   return ((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0));
}

/* Returns longest side of three given sides. */
long long longest_side(long long A, long long B, long long C)
{
    long long longest = A;
    if (B > longest)
        longest = B;
    if (C > longest)
        longest = C;
    return longest;
}

/* Returns 0 if sides form a right triangle; > 0 if sides form an acute triangle;
 < 0 if sides form obtuse triangle. */
long long angle_type(long long A, long long B, long long C, long long *pts)
{
    long long hypotenuse = longest_side(A, B, C);
    
    if (A == hypotenuse)
        return dot_product((pts[2] - pts[4]), (pts[3] - pts[5]), (pts[0] - pts[4]), (pts[1] - pts[5]));
    if (B == hypotenuse)
        return dot_product((pts[2] - pts[0]), (pts[3] - pts[1]), (pts[4] - pts[0]), (pts[5] - pts[1]));
    return dot_product((pts[0] - pts[2]), (pts[1] - pts[3]), (pts[4] - pts[2]), (pts[5] - pts[3]));
}

int main(int argc, char *argv[])
{
    long long pts[6]; /* Array to hold coordinate values. */
    long long A, B, C; /* Length of sides. */
    int i; /* Iteration variable. */
    
    /* Convert and save command line parameters. */
    for (i = 0; i < argc - 1; i++)
       pts[i] = atoll(argv[i + 1]);
    
    /* Check for collinearity. */
    if ((pts[0] * (pts[3] - pts[5]) + pts[2] * (pts[5] - pts[1]) + pts[4] * (pts[1] - pts[3])) == 0)
    {
        printf("not a triangle\n");
        exit(EXIT_SUCCESS);
    }
    
    /* Compute the squared length of sides of triangle. */
    A = sqd_dst(pts[0], pts[1], pts[2], pts[3]);
    B = sqd_dst(pts[2], pts[3], pts[4], pts[5]);
    C = sqd_dst(pts[4], pts[5], pts[0], pts[1]);
    
    if ( (A == B) || (A == C) || (B == C) )
        printf("isosceles ");
    else
        printf("scalene ");
    
    long long type = angle_type(A, B, C, pts);
    
    if (type == 0)
        printf("right\n");
    else if (type > 0)
        printf("acute\n");
    else
        printf("obtuse\n");
    
    exit(EXIT_SUCCESS);      
}
