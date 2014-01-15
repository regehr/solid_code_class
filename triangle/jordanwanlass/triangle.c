#include <stdio.h>
#include <math.h>

struct triangle {
	long long ax;
	long long ay;
	long long bx;
	long long by;
	long long cx;
	long long cy;
	long long A;
	long long B;
	long long C;
};

void getSides(struct triangle *triangle){
 	long long ax = (*triangle).ax;
 	long long ay = (*triangle).ay; 
 	long long bx = (*triangle).bx; 
 	long long by = (*triangle).by; 
 	long long cx = (*triangle).cx; 
 	long long cy = (*triangle).cy; 
 	  	 
 	(*triangle).C = pow((ax - bx),2) + pow((ay - by), 2);
 	(*triangle).A = pow((bx - cx),2) + pow((by - cy), 2);
 	(*triangle).B = pow((cx - ax),2) + pow((cy - ay), 2);	   
}

// double getLargestAngle(long long a, long long b, long long c) {
// 
// 	double eq = acos(((b*b) + (c*c) - (a*a))/(2.0*b*c));
// 	
// 	double angle = eq * (180/M_PI);
// 
// 	return angle;
// }

long findAngle(long ax, long ay, long bx, long by) {
	return (ax * bx) + (ay * by);	
}

char getLongSide(struct triangle triangle) {	
	char longSide = 'A';
	long long max = 0;
	if(triangle.A > triangle.B) {
		max = triangle.A;	
	} else {
		longSide = 'B';
		max = triangle.B;
	}
	
	return ((max > triangle.C) ? longSide : 'C');
}

// char * findTriangle(struct triangle triangle){
// 	char longestSide = getLongSide(triangle);
// 	long double largest = 0.0;
// 	
// 	if(longestSide == 'A') {
// 		largest = getLargestAngle(triangle.A, triangle.B, triangle.C);
// 	} else if(longestSide == 'B') {
// 		largest = getLargestAngle(triangle.B, triangle.A, triangle.C);
// 	} else {
// 		largest = getLargestAngle(triangle.C, triangle.A, triangle.B);
// 	}
// 	
// 	if((largest - 90.0) < .00000000001 && (largest - 90.0) > 0) {
// 		return "right";
// 	} else if((largest - 90.0) > .00000000001) {
// 		return "obtuse";
// 	} else {
// 		return "acute";
// 	}
// 	
// }

char * findTriangle(struct triangle triangle) {
	
	long long ax = triangle.ax;
 	long long ay = triangle.ay; 
 	long long bx = triangle.bx; 
 	long long by = triangle.by; 
 	long long cx = triangle.cx; 
 	long long cy = triangle.cy; 
 	
	char longSide = getLongSide(triangle);
	
	long angle = 0;
	if(longSide == 'A') {
		angle = findAngle((bx - ax), (by - ay), (cx - ax), (cy - ay));
	} else if(longSide = 'B') {
		angle = findAngle((cx - bx), (cy - by), (ax - bx), (ay - by));
	} else {
		angle = findAngle((bx - cx), (by - cy), (ax - cx), (ay - cy));
	}
	
	if(angle == 0) {
		return "right";
	} else if(angle > 0) {
		return "acute";
	} else {
		return "obtuse";
	}
}

char * findType(struct triangle triangle) {
	int bool = 	triangle.A == triangle.B 
				|| triangle.B == triangle.C 
				|| triangle.C == triangle.A;
	
	return bool ? "isosceles" : "scalene";
}

void setup(struct triangle *triangle, char *argv[]) {
	long long inputs[6];
	 
	int i;
	for(i = 0; i < 6; i++) {
		inputs[i] = atoll(argv[i+1]);
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

int main(int argc, char *argv[]) {
	struct triangle triangle = {0};
	
	if(argc == 7) {
	 	setup(&triangle, argv);
	} else {
		printf("not a triangle\n");
		return 0;
	}

    getSides(&triangle);
      
    if(collinearCheck(triangle)) {
    	printf("not a triangle\n");
    	return 0;
    }
    
    

     printf("%s %s\n",findType(triangle),findTriangle(triangle));
    
	return 0;
}