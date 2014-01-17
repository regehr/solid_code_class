#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct Point
{
	long long x;
	long long y;
};

bool is_nat(struct Point p1, struct Point p2, struct Point p3);
long long sq_dist(struct Point p1, struct Point p2);
double det_angle(double a, double b, double c);
bool is_right(struct Point p1, struct Point p2, struct Point p3);

int main(int argc, char* argv[])
{
	//Local vars
	struct Point p1, p2, p3;
	double ab, bc, ac;
	double AB, BC, AC;
	
	//Validate correct number of inputs
	assert(argc == 7);
	
	//Parse command line input
	p1.x = atoi(argv[1]); p1.y = atoi(argv[2]);
	p2.x = atoi(argv[3]); p2.y = atoi(argv[4]);
	p3.x = atoi(argv[5]); p3.y = atoi(argv[6]);
	
	//NOT A TRIANGLE case
	if(is_nat(p1, p2, p3))
	{
		printf("not a triangle\n");
		return 0;
	}
	
	//Determine the distances between the points
	ab = sqrt(sq_dist(p1, p2));
	bc = sqrt(sq_dist(p2, p3));
	ac = sqrt(sq_dist(p1, p3));
	
	//Determine the angles between the points
	AB = det_angle(ac, bc, ab);
	BC = det_angle(ab, ac, bc);
	AC = det_angle(ab, bc, ac);
	
	//Determine type of triangle
	if(ab == bc || bc == ac || ab == ac)
		printf("isosceles");
	else
		printf("scalene");
		
	//Determine type of angles
	double right = M_PI/2;
	
	if(is_right(p1, p2, p3))
		printf(" right\n");
	else if(AB > right || BC > right || AC > right)
		printf(" obtuse\n");
	else
		printf(" acute\n");
	
	exit(0);
}

/* Check given points to see if they are collinear */
bool is_nat(struct Point p1, struct Point p2, struct Point p3)
{
	if((p1.x*(p2.y-p3.y) + p2.x*(p3.y-p1.y) + p3.x*(p1.y-p2.y)) == 0)
		return true;
	else
		return false;
}

/* Determine the squared distance between two points */
long long sq_dist(struct Point p1, struct Point p2)
{
	return pow((p2.x-p1.x), 2ll) + pow((p2.y-p1.y), 2ll);
}

double det_angle(double a, double b, double c)
{
	double numerator, denominator;
	
	numerator = pow(a, 2) + pow(b, 2) - pow(c, 2);
	denominator = 2 * a * b;
	
	assert(denominator != 0);
	
	return acos(numerator/denominator);
}

bool is_right(struct Point p1, struct Point p2, struct Point p3)
{
	bool r1, r2, r3;
	
	r1 = (sq_dist(p1, p2) + sq_dist(p2, p3) == sq_dist(p1, p3));
	r2 = (sq_dist(p2, p3) + sq_dist(p1, p3) == sq_dist(p1, p2));
	r3 = (sq_dist(p1, p2) + sq_dist(p1, p3) == sq_dist(p2, p3));
	
	return (r1 || r2 || r3);
}
