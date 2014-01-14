#include <stdio.h>
#include <math.h>

struct triangle {
	long double ax;
	long double ay;
	long double bx;
	long double by;
	long double cx;
	long double cy;
	long double A;
	long double B;
	long double C;
};

void getSides(struct triangle *triangle){
 	long double ax = (*triangle).ax;
 	long double ay = (*triangle).ay; 
 	long double bx = (*triangle).bx; 
 	long double by = (*triangle).by; 
 	long double cx = (*triangle).cx; 
 	long double cy = (*triangle).cy; 
 	  	 
 	(*triangle).C = sqrt(pow((ax - bx),2) + pow((ay - by), 2));
 	(*triangle).A = sqrt(pow((bx - cx),2) + pow((by - cy), 2));
 	(*triangle).B = sqrt(pow((cx - ax),2) + pow((cy - ay), 2));	   
}

double getLargestAngle(long double a, long double b, long double c) {

	double eq = acos(((b*b) + (c*c) - (a*a))/(2.0*b*c));
	
	double angle = eq * (180/M_PI);

	return angle;
}

char getLongSide(struct triangle triangle) {	
	char longSide = 'A';
	long double max = 0.0;
	if(triangle.A > triangle.B) {
		max = triangle.A;	
	} else {
		longSide = 'B';
		max = triangle.B;
	}
	
	return ((max > triangle.C) ? longSide : 'C');
}

char * findTriangle(struct triangle triangle){
	char longestSide = getLongSide(triangle);
	long double largest = 0.0;
	
	if(longestSide == 'A') {
		largest = getLargestAngle(triangle.A, triangle.B, triangle.C);
	} else if(longestSide == 'B') {
		largest = getLargestAngle(triangle.B, triangle.A, triangle.C);
	} else {
		largest = getLargestAngle(triangle.C, triangle.A, triangle.B);
	}
	
	if((largest - 90.0) < .00000000001 && (largest - 90.0) > 0) {
		return "right";
	} else if((largest - 90.0) > .00000000001) {
		return "obtuse";
	} else {
		return "acute";
	}
	
}

char * findType(struct triangle triangle) {
	int bool = 	triangle.A == triangle.B 
				|| triangle.B == triangle.C 
				|| triangle.C == triangle.A;
	
	return bool ? "isosceles" : "scalene";
}

void setup(struct triangle *triangle, char *argv[]) {
	long double inputs[6];
	 
	int i;
	for(i = 0; i < 6; i++) {
		int temp = atoi(argv[i+1]);
		inputs[i] = (long double)temp;
	}
	
	(*triangle).ax = inputs[0];
	(*triangle).ay = inputs[1];
	(*triangle).bx = inputs[2];
	(*triangle).by = inputs[3];
	(*triangle).cx = inputs[4];
	(*triangle).cy = inputs[5];		
}

int collinearCheck(struct triangle triangle) {
	int bool = 	((triangle.ax*(triangle.by - triangle.cy)) +
				(triangle.bx*(triangle.cy - triangle.ay)) +
				(triangle.cx*(triangle.ay - triangle.by))) == 0;
	return bool;
}

int validPoints(struct triangle triangle) {
	return ((triangle.A > 0) && (triangle.B > 0) && (triangle.C > 0));
}

int main(int argc, char *argv[]) {
	struct triangle triangle = {0.0};
	
	if(argc == 7) {
	 	setup(&triangle, argv);
	} else {
		printf("not a triangle\n");
		return 0;
	}

    getSides(&triangle);
      
    if(collinearCheck(triangle) || !validPoints(triangle)) {
    	printf("not a triangle\n");
    	return 0;
    }
    
    

     printf("%s %s\n",findType(triangle),findTriangle(triangle));
    
//     printf("%llf is Struct A\n", triangle.A);
//     printf("%llf is Struct B\n", triangle.B);
//     printf("%llf is Struct C\n", triangle.C);
//     printf("%c This is the longest Struct side\n", getLongSide(triangle));
	return 0;
}