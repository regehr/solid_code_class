#include <stdio.h>
#include <math.h>


void getSideLengths(long double ax,long double ay, long double bx, long double by, 
	long double cx, long double cy, long double * A, long double * B, long double * C){
 	
 	*C = sqrt(pow((ax - bx),2) + pow((ay - by), 2));
 	*A = sqrt(pow((bx - cx),2) + pow((by - cy), 2));
 	*B = sqrt(pow((cx - ax),2) + pow((cy - ay), 2));	   
}

char getLongSide(long double * A, long double * B, long double * C) {
	
	char longSide = 'A';
	long double max = 0.0;
	if(*A > *B) {
		max = *A;	
	} else {
		longSide = 'B';
		max = *B;
	}
	
	return ((max > *C) ? longSide : 'C');
}

int main(int argc, char *argv[]) {
    
    if (argc < 6) {
        printf("hello\n");
    }
    
    long double A = 0.0;
    long double B = 0.0;
    long double C = 0.0;
    getSideLengths(0,0,0,1,1,0,&A, &B, &C);
    
    printf("%llf is A\n", A);
    printf("%llf is B\n", B);
    printf("%llf is C\n", C);
    printf("%c This is the longest side\n", getLongSide(&A,&B,&C));
}