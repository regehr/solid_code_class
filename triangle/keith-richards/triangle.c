#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct _point 
{
    unsigned long long x;
    unsigned long long y;
} Point;

/*
 * squares a long long
 */
unsigned long long square(unsigned long long x)
{
    return x*x;
}

/*
 * returns one if the points are collinear
 */
int collinear(Point points[])
{
    return (points[0].x * (points[1].y - points[2].y)) + 
	   (points[1].x * (points[2].y - points[0].y)) + 
	   (points[2].x * (points[0].y - points[1].y)) == 0;
}

/*
 * prints "obtuse" if the longest side is longer than the sum of the other two sides of a triangle
 * prints "acute" if the longest side is shorter than the sum of the other two sides of a triangle
 * prints "right" otherwise
 */
void print_angle(unsigned long long lengths[])
{
    if (lengths[2] > (lengths[1] + lengths[0]))
    {
	puts("obtuse");
    }
    else if (lengths[2] < (lengths[1] + lengths[0]))
    {
	puts("acute");
    }
    else
    {
	puts("right");
    }
}

/*
 * prints "isosceles" if two sides are equal in length
 * prints "scalene" otherwise
 */
void print_type(unsigned long long lengths[])
{
    if (lengths[0] == lengths[1] || lengths[2] == lengths[1])
    {
	printf("isosceles ");
    }
    else
    {
	printf("scalene ");
    }
}

/*
 * comparison for two unsigned long longs
 */
int comp(const void *a, const void *b) 
{
    unsigned long long *x = (unsigned long long *) a;
    unsigned long long *y = (unsigned long long *) b;
    if (*x > *y)
    {
	return 1;
    }
    if (*y > *x)
    {
	return -1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    Point points[3];
    unsigned long long side_lengths[3];
    
    points[0].x = atol(argv[1]);
    points[0].y = atol(argv[2]);
    points[1].x = atol(argv[3]);
    points[1].y = atol(argv[4]);
    points[2].x = atol(argv[5]);
    points[2].y = atol(argv[6]);

    // run a quick check to remove the not a triangle cases
    if (collinear(points))
    {
	puts("not a triangle");
	return 0;
    }

    side_lengths[0] = square(points[0].x - points[1].x) + square(points[0].y - points[1].y);
    side_lengths[1] = square(points[1].x - points[2].x) + square(points[1].y - points[2].y);
    side_lengths[2] = square(points[0].x - points[2].x) + square(points[0].y - points[2].y);

    qsort(side_lengths, 3, sizeof(unsigned long long), comp);

    print_type(side_lengths);
    print_angle(side_lengths);

    return 0;
}
