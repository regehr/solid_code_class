#include <stdio.h>
#include <math.h>

struct triangle {	
	long long A;
	long long B;
	long long C;
};

struct pts {
	long long ax;
	long long ay;
	long long bx;
	long long by;
	long long cx;
	long long cy;
};

/*	distance between two points, squared */
long long squaredDistance(long long ax, long long ay, long long bx, long long by) {
	return pow(bx - ax, 2) + pow(by - ay, 2);
}

/* 	get the squared length of the sides of the triangle */
void getSides(struct triangle *triangle, struct pts pts){
	(*triangle).A = squaredDistance(pts.ax, pts.ay, pts.bx, pts.by);
	(*triangle).B = squaredDistance(pts.bx, pts.by, pts.cx, pts.cy);
	(*triangle).C = squaredDistance(pts.cx, pts.cy, pts.ax, pts.ay);		   
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
char * findTriangle(struct pts pts, struct triangle triangle) {
	
	char longSide = getLongSide(triangle);
	
	long angle = 0;
	if(longSide == 'A') {
		angle = findAngle((pts.bx - pts.cx), 
		(pts.by - pts.cy), (pts.ax - pts.cx), (pts.ay - pts.cy));
	} else if(longSide == 'B') {
		angle = findAngle((pts.bx - pts.ax), 
		(pts.by - pts.ay), (pts.cx - pts.ax), (pts.cy - pts.ay));
	} else {
		angle = findAngle((pts.ax - pts.bx), 
		(pts.ay - pts.by), (pts.cx - pts.bx), (pts.cy - pts.by));
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
int collinearCheck(struct pts pts) {								
	int bool =	((pts.ax * (pts.by - pts.cy)) +
				(pts.bx * (pts.cy - pts.ay)) +
				(pts.cx * (pts.ay - pts.by))) == 0;
					
	return bool;
}

/*	initialize all the points in our points struct */
void setup(struct pts *pts, char *argv[]) {
	long long inputs[6];

	int i;
	for(i = 0; i < 6; i++) {
		inputs[i] = atoll(argv[i + 1]);
	}
	
	(*pts).ax = inputs[0];
	(*pts).ay = inputs[1];
	(*pts).bx = inputs[2];
	(*pts).by = inputs[3];
	(*pts).cx = inputs[4];
	(*pts).cy = inputs[5];	
}

int main(int argc, char *argv[]) {
	struct triangle triangle = {0};
	struct pts pts = {0};

	if(argc == 7) {		
		setup(&pts, argv);		
	} else {
		printf("not a triangle\n");
		return 0;
	}

    getSides(&triangle, pts);
    
    if(collinearCheck(pts)) {
    	printf("not a triangle\n");
    	return 0;
    }
    
    printf("%s %s\n",findType(triangle),findTriangle(pts, triangle));
    
	return 0;
}