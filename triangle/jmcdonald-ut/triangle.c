/*
 * Identifies important information about triangles.  Not yet tested.  
 *
 * Laser Life - Blood Brothers
 *
 * @author Jonathon McDonald <jmcdonald.ut@gmail.com>
 */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*
 * Struct that represents a point
 */
struct point {
	int x;
	int y;
};


/*
 * Determines the length between two points
 */
double get_length (struct point p1, struct point p2)
{
	double part1, part2, sum;
	
	part1 = pow((p2.x - p1.x), 2.0);
	part2 = pow((p2.y - p1.y), 2.0);

	sum = part1 + part2;
	
	return sqrt(sum);
}


/*
 * Gets an angle between two points
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
 * Convert radians to degrees
 */
double in_degrees (double num)
{
	return num * 180 / M_PI;
}


/*
 * Is this not a triangle?
 */
int is_nat (double len1, double len2, double len3)
{
	return (len1 == 0.0 || len2 == 0.0 || len3 == 0.0);
}


/*
 * Is this triangle obtuse?
 */
int is_obtuse (double ang1, double ang2, double ang3)
{
	return (ang1 > 1.57079633 || ang2 > 1.57079633 || ang3 > 1.57079633);
}


/*
 * Is this triangle acute?
 */
int is_acute (double ang1, double ang2, double ang3)
{
	return (ang1 < 1.57079633 && ang2 < 1.57079633 && ang3 < 1.57079633);
}


/*
 * Is this triangle equilateral?
 */
int is_equilateral (double len1, double len2, double len3)
{
	return (len1 == len2 && len1 == len3 && len2 == len3);
}


/*
 * Is this triangle iso?
 */
int is_iso (double len1, double len2, double len3)
{
	return (len1 == len2 || len1 == len3 || len2 == len3);
}


/*
 * Builds a point with the given string
 */
struct point new_point (char * num1, char * num2)
{
	struct point current;

	current.x = atof(num1);
	current.y = atof(num2);

	return current;
}


/*
 * Blood brothers - laser life?
 *
 * ummm...i'll refactor this..fasho
 */
int main (int argc, char * argv[])
{
	int i;
	double len_p1_p2, len_p2_p3, len_p1_p3;
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

	if (is_nat(len_p1_p2, len_p2_p3, len_p1_p3)) {
		printf("not a triangle\n");
		return 0;
	}

	if (is_equilateral(len_p1_p2, len_p2_p3, len_p1_p3)) {
		printf("equilateral ");
	} else if (is_iso(len_p1_p2, len_p2_p3, len_p1_p3)) {
		printf("isosceles ");
	} else {
		printf("scalene ");
	}

	if (is_acute(ang_p1_p2, ang_p1_p3, ang_p2_p3)) {
		printf("acute\n");
	} else if (is_obtuse(ang_p1_p2, ang_p1_p3, ang_p2_p3)) {
		printf("obtuse\n");
	} else {
		printf("right\n");
	}

	return 0;
}