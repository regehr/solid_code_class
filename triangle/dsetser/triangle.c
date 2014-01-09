#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// Triangle Analyzer written by Daniel Setser
// This program takes in 6 positive integers, which represent 3 points 
// forming a triangle. It outputs two words describing what kind of
// triangle was given as input, or "not a triangle". The first word will be
// scalene,  isosceles, or equilateral. The second word will be acute,
// right, or obtuse.

struct Point
{
	double x;
	double y;
};

double distance(struct Point a, struct Point b)
{
	return sqrt(((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)));
}

int equalsTolerance(double a, double b)
{
	return abs(a-b) <= .0000000001;
}

int isRight(double angleA, double angleB, double angleC)
{
	return equalsTolerance(angleA, 90) || equalsTolerance(angleB, 90) 
      || equalsTolerance(angleC, 90);
}

void printType(double angleA, double angleB, double angleC)
{
	if(isRight(angleA, angleB, angleC))
		printf("right\n");
	else if(angleA > 90 || angleB > 90 || angleC > 90)
		printf("obtuse\n");
	else
		printf("acute\n");
}

int main(int argc, char* argv[])
{
  struct Point a, b, c;
	double ab;
	double ac;
	double bc;
	double angleA;
	double angleB;
	double angleC;


	if(argc < 7)
	{
		printf("Not enough args\n");
		return 0;
	}

	a.x = atoi(argv[1]);
	a.y = atoi(argv[2]);
	b.x = atoi(argv[3]);
	b.y = atoi(argv[4]);
	c.x = atoi(argv[5]);
	c.y = atoi(argv[6]);

	// Check if the points are collinear
	if(((b.y - a.y) * (c.x - b.x)) == ((c.y - b.y) * (b.x - a.x)))
	{
		printf("not a triangle\n");
		return 0;
	}

	// Find the sides
	ab = distance(a, b);
	ac = distance(a, c);
	bc = distance(b, c);

	// Find the angles
	angleA = acos(((ab*ab) + (ac*ac) - (bc*bc)) / (2 * ab * ac)) * (180/M_PI);
	angleB = acos(((ab*ab) - (ac*ac) + (bc*bc)) / (2 * ab * bc)) * (180/M_PI);
	angleC = acos(((ac*ac) - (ab*ab) + (bc*bc)) / (2 * bc * ac)) * (180/M_PI);

	if(ab == ac && ab == bc) // Equilateral
		printf("equilateral acute\n");
	else if(ab == ac || ab == bc || ac == bc) // Isosceles
	{
		printf("isosceles ");
		printType(angleA, angleB, angleC);
	}
	else // Scalene
	{
		printf("scalene ");
		printType(angleA, angleB, angleC);
	}
}

