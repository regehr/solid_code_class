/* Jake Guckert */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


long long get_side_length_squared(long long x2, long long x1, long long y2, long long y1) {
	long long x = pow((x2 - x1), 2ll);
	long long y = pow((y2 - y1), 2ll);

	long long length = x + y;
	
	return length;
}

/* returns the length of one side of the triangle */
double get_side_length(long long x2, long long x1, long long y2, long long y1) {
	return sqrt(get_side_length_squared(x2, x1, y2, y1));
}

/* returns the angle between two points */
double get_angle(double a, double b, double c) {
	double a_squared = pow(a, 2.0);
	double b_squared = pow(b, 2.0);
	double c_squared = pow(c, 2.0);

	double top = a_squared + b_squared - c_squared;
	double bottom = 2.0 * a * b;
	double quotient = top / bottom;

	return acos(quotient);
}

/* determines whether the given side lengths make a triangle. */
int is_a_triangle(double x1_x2_length, double x2_x3_length, double x1_x3_length) {
	double r1 = x1_x2_length + x2_x3_length;
	double r2 = x1_x2_length + x1_x3_length;
	double r3 = x2_x3_length + x1_x3_length;
	
	return (r1 > x1_x3_length && r2 > x2_x3_length && r3 > x1_x2_length);
}

int is_scalene(double x1_x2_length, double x2_x3_length, double x1_x3_length) {
	return (x1_x2_length != x2_x3_length && x1_x2_length != x1_x3_length && x2_x3_length != x1_x3_length);
}

int is_right(double a, double b, double c) {
	double a_squared = pow(a, 2.0);
	double b_squared = pow(b, 2.0);
	double c_squared = pow(c, 2.0);

	int r1 = a_squared + b_squared == c_squared;
	int r2 = b_squared + c_squared == a_squared;
	int r3 = c_squared + a_squared == b_squared;
	
	return (r1 || r2 || r3);
}

int is_acute(double x1_x2_angle, double x2_x3_angle, double x1_x3_angle) {
	return(x1_x2_angle < 1.57079633 && x2_x3_angle < 1.57079633 && x1_x3_angle < 1.57079633);
}

int main(int argc, char* argv[]) {
	
	long long x1 = atof(argv[1]);
	long long y1 = atof(argv[2]);
	long long x2 = atof(argv[3]);
	long long y2 = atof(argv[4]);
	long long x3 = atof(argv[5]);
	long long y3 = atof(argv[6]);

	double x1_x2_length = get_side_length(x2, x1, y2, y1);
	double x2_x3_length = get_side_length(x3, x2, y3, y2);
	double x1_x3_length = get_side_length(x3, x1, y3, y1);

	double x1_x2_angle = get_angle(x1_x2_length, x2_x3_length, x1_x3_length);
	double x2_x3_angle = get_angle(x2_x3_length, x1_x3_length, x1_x2_length);
	double x1_x3_angle = get_angle(x1_x3_length, x1_x2_length, x2_x3_length);

	if(!is_a_triangle(x1_x2_length, x2_x3_length, x1_x3_length)) {
		printf("not a triangle\n");
		exit(0);
	}

	if(is_scalene(x1_x2_length, x2_x3_length, x1_x3_length))
		printf("scalene ");
	else
		printf("isosceles ");
	
	if(is_right(x1_x2_length, x2_x3_length, x1_x3_length))
		printf("right\n");
	
	if(is_acute(x1_x2_angle, x2_x3_angle, x1_x3_angle))
		printf("acute\n");
	else
		printf("obtuse\n");

	/*printf("x1_x2_length: %f\n", x1_x2_length);
	printf("x2_x3_length: %f\n", x2_x3_length);
	printf("x1_x3_length: %f\n", x1_x3_length);
	printf("x1_x2_angle: %f\n", x1_x2_angle);
	printf("x2_x3_angle: %f\n", x2_x3_angle);
	printf("x1_x3_angle: %f\n", x1_x3_angle);*/
	
	return 0;
}