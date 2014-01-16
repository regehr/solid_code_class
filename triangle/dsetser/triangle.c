#include "stdio.h"
#include "stdlib.h"

/* Triangle Analyzer written by Daniel Setser
 * This program takes in 6 positive integers, which represent 3 points 
 * forming a triangle. It outputs two words describing what kind of
 * triangle was given as input, or "not a triangle". The first word will be
 * scalene,  isosceles, or equilateral. The second word will be acute,
 * right, or obtuse.
 */

struct Point
{
	long x;
	long y;
};

long distanceSquared(struct Point a, struct Point b)
{
	return ((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y));
}

void printType(long a, long long int b, long long int c)
{
	// Print the first word.
	if(a == b || a == c || b == c)
	{
		printf("isosceles ");
	}
	else
	{
		printf("scalene ");
	}

	// Make sure a is the max.
	long temp;
	if(b > a && b > c)
	{
		temp = b; b = a; a = temp; }
	else if(c > a && c > b)
	{	
		temp = c;
		c = a;
		a = temp;
	}

	// Print the second word.
	if(a - c == b) // b + c == a avoiding overflow
		printf("right\n");
	else if(a - c < b) // b + c > a avoiding overflow
		printf("acute\n");
	else
		printf("obtuse\n");
}

int main(int argc, char* argv[])
{
  struct Point a, b, c;
	long ab, ac, bc;

	// Store arguments into points
	a.x = atoi(argv[1]);
	a.y = atoi(argv[2]);
	b.x = atoi(argv[3]);
	b.y = atoi(argv[4]);
	c.x = atoi(argv[5]);
	c.y = atoi(argv[6]);

	// Check if the points are collinear.
	if(((b.y - a.y) * (c.x - b.x)) == ((c.y - b.y) * (b.x - a.x)))
	{
		printf("not a triangle\n");
		return 0;
	}

	// Find the sides squared.
	ab = distanceSquared(a, b);
	ac = distanceSquared(a, c);
	bc = distanceSquared(b, c);

	printType(ab, ac, bc);
}

