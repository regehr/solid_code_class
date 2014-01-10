#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * This is my own little max function for 3 doubles.  I use it to find the 
 * largest angle from all three angles
 */
double max(double a, double b, double c)
{
    double largest = a;

    if (b > largest)
    {
	largest = b;
    }
    if (c > largest)
    {
	largest = c;
    }
    
    return largest;
}


int main(int argc, char *argv[])
{
    // I am going to skip error checking since we can.
    // first peel off the arguments
    unsigned int x1 = atoi(argv[1]);
    unsigned int y1 = atoi(argv[2]);
    unsigned int x2 = atoi(argv[3]);
    unsigned int y2 = atoi(argv[4]);
    unsigned int x3 = atoi(argv[5]);
    unsigned int y3 = atoi(argv[6]);

    // run a quick check to remove the not a triangle cases
    // three points are said to be collinear when the following formula is 0
    if ((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2)) == 0)
    {
	puts("not a triangle");
	return 0;
    }

    double a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    double b = sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3));
    double c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));

    // find the angles using the law of cosines
    double angle_a = acos(((b * b) + (c * c) - (a * a))/(2 * b * c));
    double angle_b = acos((c * c + a * a - b * b)/(2 * c * a));    
    double angle_c = M_PI - angle_a - angle_b;
    double largest_angle = max(angle_a, angle_b, angle_c);

    // check the side lengths
    if (a == b || b == c || a == c)
    {
	printf("isosceles ");
    }
    else
    {
	printf("scalene ");
    }

    // here I am making a tolerance for round off errors.  There
    // is probably a better way to do this
    double ratio = largest_angle / (M_PI / 2);

    // check the largest angle    
    if (ratio >= .99999 && ratio <= 1.00001)
    {
	printf("right\n");
    }
    else if (largest_angle > (M_PI / 2))
    {
	printf("obtuse\n");
    }
    else
    {
	printf("acute\n");
    }

    return 0;
}




