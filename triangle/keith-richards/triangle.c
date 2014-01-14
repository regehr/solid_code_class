#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long double max(long double a, long double b, long double c)
{
    long double largest = a;
    if (b > largest)
	largest = b;
    if (c > largest)
	largest = c;
    return largest;
}

long double min(long double a, long double b, long double c)
{
    long double smallest = a;
    if (b < smallest)
	smallest = b;
    if (c < smallest)
	smallest = c;
    return smallest;
}


long double mid(long double a, long double b, long double c)
{
    if ((a < b && a > c) ||
	(a < c && a > b))
    {
	return a;
    }
    if ((b < a && b > c) ||
	(b < c && b > a))
    {
	return b;
    }
    if ((c < a && c > b) ||
	(c < b && c > a))
    {
	return c;
    }

    return 0;
}



/*
 * A function that determines if a triangle is right, without using acos or any other heavy flop
 */
int is_right(long long x1, long long y1, 
	  long long x2, long long y2,
	  long long x3, long long y3)
{
    
    if ((y2 - y1) == 0)
    {
	return ((x3 == x1) || (x3 == x2));
    }
    if ((x2 - x1) == 0)
    {
	return ((y3 == y1) || (y3 == y2));
    }

    long double slope_num = x1 - x2;
    long double slope_den = y2 - y1;
    long double point     = x3 - x1;
    
    return y3 == (slope_num/slope_den)*point + y1;
}




/*
 * A function that determines if a triangle is obtuse, without using acos or any other heavy flop
 */
int is_obtuse(long double a, long double b, long double c)
{
    long double largest  = max(a, b, c);
    long double smallest = min(a, b, c); 
    long double median   = mid(a, b, c);

    // iscoseles case will get into here.  There are two medians (or maxes, or whatever) so we do this
    if (median == 0)
    {
	if (a == b)
	{
	    return a < sqrt(2)/2*c;
	}
	if (b == c)
	{
	    return b < sqrt(2)/2*a;
	}
	if (a == c)
	{
	    return c < sqrt(2)/2*b;
	}
    }

    long double small_squared = smallest * smallest;
    long double median_squared = median * median;

    return largest > sqrt(small_squared + median_squared);
}


int main(int argc, char *argv[])
{
    // I am going to skip error checking since we can.
    // first peel off the arguments
    long long x1 = atoi(argv[1]);
    long long y1 = atoi(argv[2]);
    long long x2 = atoi(argv[3]);
    long long y2 = atoi(argv[4]);
    long long x3 = atoi(argv[5]);
    long long y3 = atoi(argv[6]);

    // run a quick check to remove the not a triangle cases
    // three points are said to be collinear when the following formula is 0
    if ((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2)) == 0)
    {
	puts("not a triangle");
	return 0;
    }

    long double a = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    long double b = (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3);
    long double c = (x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3);
   
    // check the side lengths
    if (a == b || b == c || a == c)
    {
	printf("isosceles ");
    }
    else
    {
	printf("scalene ");
    }

    a = sqrt(a);
    b = sqrt(b);
    c = sqrt(c);

    if (is_right(x1, y1, x2, y2, x3, y3) ||
	is_right(x2, y2, x3, y3, x1, y1) ||
	is_right(x3, y3, x1, y1, x2, y2))
    {
	printf("right\n");
    }
    else if (is_obtuse(a, b, c))
    {
	printf("obtuse\n");
    }
    else
    {
	printf("acute\n");
    }

    return 0;
}




