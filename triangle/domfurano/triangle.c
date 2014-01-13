/*
 * Dominic Furano
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Returns the dot product of two vectors. If the two vectors are acute,
   the dot product is positive. If the two vectors are obtuse, the dot product
   is negative. If the two vectors are perpendicular, the dot product is zero. */
long double dot_product(long double x0, long double y0, long double x1, long double y1)
{
    return (x0 * x1) + (y0 * y1);
}

/* Returns the distance between two vectors. */
long double distance(long double x0, long double y0, long double x1, long double y1)
{
    return sqrtl((powl((x1 - x0), 2.0) + powl((y1 - y0), 2.0)));
}

/* Returns longest side of three given sides. */
long double longest_side(long double A, long double B, long double C)
{
    long double longest = A;
    if (B > longest)
        longest = B;
    if (C > longest)
        longest = C;
    return longest;
}

/* Returns 0 if sides form a right triangle; > 0 if sides form an acute triangle;
 < 0 if sides form obtuse triangle. */
long double angle_type(long double A, long double B, long double C, long double *pts)
{
    long double hypotenuse = longest_side(A, B, C);
    
    if (A == hypotenuse)
        return dot_product((pts[2] - pts[4]), (pts[3] - pts[5]), (pts[0] - pts[4]), (pts[1] - pts[5]));
    if (B == hypotenuse)
        return dot_product((pts[2] - pts[0]), (pts[3] - pts[1]), (pts[4] - pts[0]), (pts[5] - pts[1]));
    return dot_product((pts[0] - pts[2]), (pts[1] - pts[3]), (pts[4] - pts[2]), (pts[5] - pts[3]));
}

int main(int argc, char *argv[])
{
    long double pts[6]; /* Array to hold coordinate values. */
    long double A, B, C; /* Length of sides. */
    int i; /* Iteration variable. */
    
    /* Convert and save command line parameters. */
    for (i = 0; i < argc - 1; i++)
        pts[i] = atof(argv[i + 1]);
    
    /* Check for collinearity. */
    if ((pts[0] * (pts[3] - pts[5]) + pts[2] * (pts[5] - pts[1]) + pts[4] * (pts[1] - pts[3])) == 0)
    {
        printf("not a triangle\n");
        exit(EXIT_SUCCESS);
    }
    
    /* Compute length of sides of triangle. */
    A = distance(pts[0], pts[1], pts[2], pts[3]);
    B = distance(pts[2], pts[3], pts[4], pts[5]);
    C = distance(pts[4], pts[5], pts[0], pts[1]);
    
    if ( (A == B) || (A == C) || (B == C) )
        printf("isosceles ");
    else
        printf("scalene ");
    
    long double type = angle_type(A, B, C, pts);
    
    if (type == 0)
        printf("right\n");
    else if (type > 0)
        printf("acute\n");
    else
        printf("obtuse\n");
    
    exit(EXIT_SUCCESS);      
}
