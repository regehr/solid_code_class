/* Jake Guckert */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* returns the length of one side of the triangle */
double get_side_length(double x2, double x1, double y2, double y1) {
	double result, x, y;

	x = pow((x2 - x1), 2);
	y = pow((y2 - y1), 2);

	return sqrt(x + y);
}

/* determines whether the given side lengths make a triangle. */
int is_a_triangle(double s1, double s2, double s3) {
	double s1_s2 = s1 + s2;
	double s1_s3 = s1 + s3;
	double s2_s3 = s2 + s3;
	return (s1_s2 > s3 && s1_s3 > s2 && s2_s3 > s1);
}

/* returns the angle between two sides of the triangle */
const char * get_angle_classification(double a, double b, double c) {
	double a_squared = pow(a, 2);
	double b_squared = pow(b, 2);
	double c_squared = pow(c, 2);

	double angle_a = acos((b_squared + c_squared - a_squared) / (2 * b * c)) * (180 / M_PI);
	double angle_b = acos((a_squared + c_squared - b_squared) / (2 * a * c)) * (180 / M_PI);
	double angle_c = acos((a_squared + b_squared - c_squared) / (2 * a * b)) * (180 / M_PI);

	printf("angle_a: %f\n", angle_a);
	printf("angle_b: %f\n", angle_b);
	printf("angle_c: %f\n", angle_c);

	if(angle_a == 90.0 || angle_b == 90.0 || angle_c == 90.0) {
		return "right\n";
	} else if (angle_a < 90.0 && angle_b < 90.0 && angle_c < 90.0) {
		return "acute\n";
	}
	return "obtuse\n";
}

const char * get_side_classification(double s1, double s2, double s3) {
	if(s1 != s2 && s1 != s3 && s2 != s3) { 
		return "scalene ";
	} else { 
		return "isosceles ";
	}
}

int main(int argc, char* argv[]) {
	
	double x0 = atof(argv[1]);
	double y0 = atof(argv[2]);

	double x1 = atof(argv[3]);
	double y1 = atof(argv[4]);

	double x2 = atof(argv[5]);
	double y2 = atof(argv[6]);

	double s1 = get_side_length(x1, x0, y1, y0);
	double s2 = get_side_length(x2, x1, y2, y1);
	double s3 = get_side_length(x2, x0, y2, y0);

	printf("side 1: %f\n", s1);
	printf("side 2: %f\n", s2);
	printf("side 3: %f\n", s3);
	
	if(!is_a_triangle(s1, s2, s3)) {
		printf("%s\n", "not a triangle");
		exit(0);
	}

	printf("%s", get_side_classification(s1, s2, s3));
	printf("%s", get_angle_classification(s1, s2, s3));
	
	return 0;
}