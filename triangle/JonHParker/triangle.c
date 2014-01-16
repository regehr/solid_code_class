/*
* Jon Parker
* (c) 1-12-2014
*
* Triangle Calculator
*
* This program takes six commandline unsigned 32 integer arguments.
* Each integer specifies an x or y coordinate of a point.
* Arguments are read in order into x1, y1, x2, y2, x3, y3.
*
* The program determines if the specified points form a triangle that is:
* 1) scalene, isosceles, or equilateral
* 2) acute, right, or obtuse
* 
* If the triangle is none of these, the result is not a triangle.
*
* Possible outputs:
* scalene acute
* scalene right
* scalene obtuse
* isosceles acute
* isosceles right
* isosceles obtuse
* equilateral acute
* not a triangle
* 
* Theoretically, equilateral acute is actually impossible in the integer domain, so that output is not expected.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* This helper function outputs the square of the length of two points.
*/
long long unsigned int GetSideSquared(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    int temp;
    if (x1 > x2)
    {
        temp = x1;
        x1 = x2;
        x2 = temp;
    }

    if (y1 > y2)
    {
        temp = y1;
        y1 = y2;
        y2 = temp;
    }
    
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

int main(int argc, char** argv) {

    // Declare variables.
    unsigned int x1, x2, x3, y1, y2, y3, v1x, v2x, v1y, v2y;
    long long unsigned int firstSideSquared, secondSideSquared, thirdSideSquared;
    char result[80];
    
    // Get arguments from commandline.
    x1 = atoi(argv[1]);
    y1 = atoi(argv[2]);
    x2 = atoi(argv[3]);
    y2 = atoi(argv[4]);
    x3 = atoi(argv[5]);
    y3 = atoi(argv[6]);
    
    // Calculate squares of lengths of each of the three sides.
    firstSideSquared = GetSideSquared(x1, y1, x2, y2);
    secondSideSquared = GetSideSquared(x1, y1, x3, y3);
    thirdSideSquared = GetSideSquared(x2, y2, x3, y3);

    // If any square of a length is 0, that means this isn't a triangle.
    if (firstSideSquared == 0 || secondSideSquared == 0 || thirdSideSquared == 0)
    {
        printf("not a triangle\n");
        return 0;
    }

    // If cross product (which is a*b*sin(theta)) is 0, then points are colinear.
    v1x = x2-x1;
    v1y = y2-y1;
    v2x = x3-x1;
    v2y = y3-y1;
    if (v1x*v2y == v2x*v1y)
    {
        printf("not a triangle\n");
        return 0;
    }

    // Determine if triangle is:
    // equilateral (three sides equal length),
    // isosceles (two sides equal length), or
    // scalene (no sides equal length)
    if (firstSideSquared == secondSideSquared && secondSideSquared == thirdSideSquared)
    {
	// THIS SHOULD BE IMPOSSIBLE.
        // However, just in case (I didn't read any proofs), leave it in.
        // Technically that means this is untested code since it is never hit.
        strcpy(result, "equilateral ");
    }
    else if (firstSideSquared == secondSideSquared || firstSideSquared == thirdSideSquared || secondSideSquared == thirdSideSquared)
    {
        strcpy(result, "isosceles ");
    }
    else
    {
        strcpy(result, "scalene ");
    }

    // Determine if triangle is:
    // acute (all angles less than 90 degrees),
    // right (one angle exactly 90 degress), or
    // obtuse (one angle greater than 90 degrees)
    //
    // Since c*c == a*a + b*b means it's a right triangle, then if c*c < a*a + b*b it is acute
    // and if c*c > a*a + b*b then it is obtuse.
    if (firstSideSquared + secondSideSquared > thirdSideSquared
        && firstSideSquared + thirdSideSquared > secondSideSquared
        && secondSideSquared + thirdSideSquared > firstSideSquared)
    {
        strcat(result, "acute\n");
    }
    else if (firstSideSquared + secondSideSquared == thirdSideSquared
        || firstSideSquared + thirdSideSquared == secondSideSquared
        || secondSideSquared + thirdSideSquared == firstSideSquared)
    {
        strcat(result, "right\n");
    }
    else
    {
        strcat(result, "obtuse\n");
    }

    printf(result);

    return 0;
}
