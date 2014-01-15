#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct point 
{
    unsigned long long x;
    unsigned long long y;
};

/*
 * squares a long long
 */
unsigned long long squared(unsigned long long x)
{
    return x*x;
}

/*
 * returns one if the points are collinear
 */
int collinear(struct point p[])
{
    return (p[0].x * (p[1].y - p[2].y)) + 
	   (p[1].x * (p[2].y - p[0].y)) + 
	   (p[2].x * (p[0].y - p[1].y)) == 0;
}

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
    struct point points[3];
    unsigned long long side_lengths[3];
    
    points[0].x = atoll(argv[1]);
    points[0].y = atoll(argv[2]);
    points[1].x = atoll(argv[3]);
    points[1].y = atoll(argv[4]);
    points[2].x = atoll(argv[5]);
    points[2].y = atoll(argv[6]);

    // run a quick check to remove the not a triangle cases
    if (collinear(points))
    {
	puts("not a triangle");
	return 0;
    }

    side_lengths[0] = squared(points[0].x - points[1].x) + squared(points[0].y - points[1].y);
    side_lengths[1] = squared(points[1].x - points[2].x) + squared(points[1].y - points[2].y);
    side_lengths[2] = squared(points[0].x - points[2].x) + squared(points[0].y - points[2].y);
    qsort(side_lengths, 3, sizeof(unsigned long long), comp);

    print_type(side_lengths);
    print_angle(side_lengths);

    return 0;
}






