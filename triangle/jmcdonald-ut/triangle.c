/*
 * Identifies important information about triangles.  Not yet tested.  
 *
 * @author Jonathon McDonald <jmcdonald.ut@gmail.com>
 */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct point {
	long long x;
	long long y;
};


/*
 * Get the length (squared) between two points.
 */
long long get_sq_len (struct point p1, struct point p2)
{
	long long part1, part2, sum;
	
	part1 = pow((p2.x - p1.x), 2ll);
	part2 = pow((p2.y - p1.y), 2ll);

	sum = part1 + part2;
	return sum;
}


/*
 * Determines the distance between two points.
 */
long long get_length (struct point p1, struct point p2)
{
	return sqrt(get_sq_len(p1, p2));
}


/*
 * Determines the angle between two edges.
 */
double get_angle (double len_a, double len_b, double len_c)
{
	// Law of cos(C) = (a^2 + b^2 - c^2) / 2 * a * b
	double asq, bsq, csq, num, den, product;

	asq = pow(len_a, 2.0);
	bsq = pow(len_b, 2.0);
	csq = pow(len_c, 2.0);

	num = asq + bsq - csq;
	den = 2.0 * len_a * len_b;

	product = num / den;

	return acos(product);
}


/*
 * Determines if this is not a triangle based on the cross product formula that
 * we covered in class.
 */
int is_nat (struct point p1, struct point p2, struct point p3)
{
	long long result1, result2, result3;

	result1 = (p1.x * (p2.y - p3.y));
	result2 = (p2.x * (p3.y - p1.y));
	result3 = (p3.x * (p1.y - p2.y));

	return ((result1 + result2 + result3) == 0);
}


/*
 * Determines if the provided points form a right triangle.
 */
int is_right (struct point p1, struct point p2, struct point p3)
{
	int result1, result2, result3;

	result1 = (get_sq_len(p1, p2) + get_sq_len(p2, p3) == get_sq_len(p1, p3));
	result2 = (get_sq_len(p2, p3) + get_sq_len(p1, p3) == get_sq_len(p1, p2));
	result3 = (get_sq_len(p1, p2) + get_sq_len(p1, p3) == get_sq_len(p2, p3));

	return (result1 || result2 || result3);
}


/*
 * Determines if this triangle is acute based on the angles.
 */
int is_acute (double ang1, double ang2, double ang3)
{
	return (ang1 < 1.57079633 && ang2 < 1.57079633 && ang3 < 1.57079633);
}


/*
 * Determines if this trinagle is isosceles based on the lengths of the edges.
 */
int is_iso (long long len1, long long len2, long long len3)
{
	return (len1 == len2 || len1 == len3 || len2 == len3);
}


/*
 * Builds a new point.
 */
struct point new_point (char * num1, char * num2)
{
	struct point current;

	current.x = atof(num1);
	current.y = atof(num2);

	return current;
}


int main (int argc, char * argv[])
{
	long long len_p1_p2, len_p2_p3, len_p1_p3;
	double ang_p1_p2, ang_p2_p3, ang_p1_p3;
	struct point p1, p2, p3;

	p1 = new_point(argv[1], argv[2]);
	p2 = new_point(argv[3], argv[4]);
	p3 = new_point(argv[5], argv[6]);

	len_p1_p2 = get_length(p1, p2);
	len_p2_p3 = get_length(p2, p3);
	len_p1_p3 = get_length(p1, p3);

	ang_p1_p2 = get_angle(len_p1_p3, len_p2_p3, len_p1_p2);
	ang_p2_p3 = get_angle(len_p1_p2, len_p1_p3, len_p2_p3);
	ang_p1_p3 = get_angle(len_p1_p2, len_p2_p3, len_p1_p3);

	if (is_nat(p1, p2, p3)) {
		printf("not a triangle\n");
		return 0;
	}

	if (is_iso(len_p1_p2, len_p2_p3, len_p1_p3)) {
		printf("isosceles ");
	} else {
		printf("scalene ");
	}

	if (is_right(p1, p2, p3)) {
		printf("right\n");
	} else if (is_acute(ang_p1_p2, ang_p1_p3, ang_p2_p3)) {
		printf("acute\n");
	} else {
		printf("obtuse\n");
	}

	return 0;
}