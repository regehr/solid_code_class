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
} triangle;

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


char getLongSide(struct triangle *triangle) {
	
	char longSide = 'A';
	long double max = 0.0;
	if((*triangle).A > (*triangle).B) {
		max = (*triangle).A;	
	} else {
		longSide = 'B';
		max = (*triangle).B;
	}
	
	return ((max > (*triangle).C) ? longSide : 'C');
}

void findTriangle(struct triangle *triangle){

}

int main(int argc, char *argv[]) {

    triangle.ax = 0.0;
    triangle.ay = 0.0;
    triangle.bx = 0.0;
    triangle.by = 1.0;
    triangle.cx = 1.0;
    triangle.cy = 0.0;
    triangle.A = 0.0;
    triangle.B = 0.0;
    triangle.C = 0.0;
    
    getSides(&triangle);
    
    printf("%llf is Struct A\n", triangle.A);
    printf("%llf is Struct B\n", triangle.B);
    printf("%llf is Struct C\n", triangle.C);
    printf("%c This is the longest Struct side\n", getLongSide(&triangle));
}