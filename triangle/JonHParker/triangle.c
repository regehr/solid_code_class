#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long unsigned int GetSideSquared(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

int main(int argc, char** argv) {

    int x1, x2, x3, y1, y2, y3;
    long long unsigned int firstSideSquared, secondSideSquared, thirdSideSquared;

    char result[80];
    
    x1 = atoi(argv[0]);
    y1 = atoi(argv[1]);
    x2 = atoi(argv[2]);
    y2 = atoi(argv[3]);
    x3 = atoi(argv[4]);
    y3 = atoi(argv[5]);
    
    firstSideSquared = GetSideSquared(x1, y1, x2, y2);
    secondSideSquared = GetSideSquared(x1, y1, x3, y3);
    thirdSideSquared = GetSideSquared(x2, y2, x3, y3);

    if (firstSideSquared == 0 || secondSideSquared == 0 || thirdSideSquared == 0)
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
        strcpy(result, "equilateral ");
    }
    else if (firstSideSquared==secondSideSquared || firstSideSquared == thirdSideSquared || secondSideSquared == thirdSideSquared)
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
    if (firstSideSquared + secondSideSquared < thirdSideSquared
        && firstSideSquared + thirdSideSquared < secondSideSquared
        && secondSideSquared + thirdSideSquared < firstSideSquared)
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
