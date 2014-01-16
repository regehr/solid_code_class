#include <stdio.h>
#include <math.h>

struct triangle {
	long long A;
	long long B;
	long long C;
};

long long squaredDistance(long long ax, long long ay, long long bx, long long by) {
	return pow(bx - ax, 2) + pow(by - ay, 2);
}

/* 	get the squared length of the sides of the triangle */
void getSides(struct triangle *triangle, long long points[]){
	(*triangle).A = squaredDistance(points[0], points[1], points[2], points[3]);
	(*triangle).B = squaredDistance(points[2], points[3], points[4], points[5]);
	(*triangle).C = squaredDistance(points[4], points[5], points[0], points[1]);	   
}

/*	find the largest angle using dot product */
long findAngle(long ax, long ay, long bx, long by) {
	return (ax * bx) + (ay * by);	
}

/* 	determine which side of the triangle is the longest */
char getLongSide(struct triangle triangle) {	
	char longSide = 'A';
	long long max = 0;
	if(triangle.A > triangle.B) {
		max = triangle.A;	
	} else {
		longSide = 'B';
		max = triangle.B;
	}
	return max > triangle.C ? longSide : 'C';
}

/* 	determine whether the triangle is right, acute or obtuse by computing the 
	angle of the longest side */
char * findTriangle(long long points[], struct triangle triangle) {

	char longSide = getLongSide(triangle);
	
	long angle = 0;
	if(longSide == 'A') {
		angle = findAngle((points[2] - points[4]), 
		(points[3] - points[5]), (points[0] - points[4]), (points[1] - points[5]));
	} else if(longSide == 'B') {
		angle = findAngle((points[2] - points[0]), 
		(points[3] - points[1]), (points[4] - points[0]), (points[5] - points[1]));
	} else {
		angle = findAngle((points[0] - points[2]), 
		(points[1] - points[3]), (points[4] - points[2]), (points[5] - points[3]));
	}
	
	if(angle == 0) {
		return "right";
	} else if(angle > 0) {
		return "acute";
	} else {
		return "obtuse";
	}
}

/*	determine whether the triangle is isosceles or scalene.  Using integer inputs,
	we will never get an equilateral triangle */
char * findType(struct triangle triangle) {
	int bool = 	triangle.A == triangle.B 
				|| triangle.B == triangle.C 
				|| triangle.C == triangle.A;
	
	return bool ? "isosceles" : "scalene";
}

/* 	determine whether the input points are collinear by calculating the double area of
	the triangle using cross product */
int collinearCheck(long long points[6]) {				
	int bool = ((points[0]*(points[3] - points[5])) +
				(points[2]*(points[5] - points[1])) + 
				(points[4]*(points[1] - points[3]))) == 0;
					
	return bool;
}

int main(int argc, char *argv[]) {
	struct triangle triangle = {0};
	long long points[6];
	if(argc == 7) {
	
		int i;
		for(i = 0; i < 6; i++) {
			points[i] = atoll(argv[i + 1]);
		}
		
	} else {
		printf("not a triangle\n");
		return 0;
	}

    getSides(&triangle, points);
      
    if(collinearCheck(points)) {
    	printf("not a triangle\n");
    	return 0;
    }
    
     printf("%s %s\n",findType(triangle),findTriangle(points, triangle));
    
	return 0;
}