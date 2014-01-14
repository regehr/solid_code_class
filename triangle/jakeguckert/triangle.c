/* Jake Guckert */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* given two points, returns the distance between those points. */
float get_side_length(int x0, int y0, int x1, int y1) {
	int temp1 = (x1 - x0) * (x1 - x0);
	int temp2 = (y1 - y0) * (y1 - y0);
	int temp3 = temp1 + temp2;
	float length = sqrt(temp3);
	return length;
}

/* returns whether the triangle is equilateral, scalene, or isosceles. */
const char * get_side_classification(float s1, float s2, float s3) {
	if(s1 == s2 && s1 == s3 && s2 == s3) {
		return "equilateral";
	}
	if(s1 != s2 && s1 != s3 && s2 != s3) {
		return "scalene";
	}
	return "isosceles";
}

/* returns whether the triangle is right, obtuse, or acute. */
const char * get_angle_classification(float a, float b, float c) {
	float a_squared = a * a;
	float b_squared = b * b;
	float c_squared = c * c;

	float angle_a = acos((b_squared + c_squared - a_squared) / (2 * b * c));
	angle_a = angle_a * (180 / M_PI);
	float angle_b = acos((c_squared + a_squared - b_squared) / (2 * c * a));
	angle_b = angle_b * (180 / M_PI);
	float angle_c = 180 - (angle_a + angle_b);

	if(angle_a == 90 || angle_b == 90 || angle_c == 90) {
		return "right";
	}
	if(angle_a > 90 || angle_b > 90 || angle_c > 90) {
		return "obtuse";
	}
	if(angle_a < 90 || angle_b < 90 || angle_c < 90) {
		return "acute";
	}
	return "";
}

/* determines whether the given side lengths make a triangle. */
int is_a_triangle(float s1, float s2, float s3) {
	float s1_s2 = s1 + s2;
	float s1_s3 = s1 + s3;
	float s2_s3 = s2 + s3;

	if((s1_s2 > s3) && (s1_s3 > s2) && (s2_s3 > s1)) {
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[]) {
	
	int x0 = atoi(argv[1]);
	int y0 = atoi(argv[2]);

	int x1 = atoi(argv[3]);
	int y1 = atoi(argv[4]);

	int x2 = atoi(argv[5]);
	int y2 = atoi(argv[6]);

	float s1 = get_side_length(x0, y0, x1, y1);
	float s2 = get_side_length(x0, y0, x2, y2);
	float s3 = get_side_length(x1, y1, x2, y2);

	if(!is_a_triangle(s1, s2, s3)) {
		printf("%s\n", "not a triangle");
		exit(0);
	}

 	printf("%s ", get_side_classification(s1, s2, s3));	
	printf("%s\n", get_angle_classification(s1, s2, s3));
	
	return 0;
}