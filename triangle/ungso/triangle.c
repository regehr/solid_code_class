#include <limits.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_type(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3);
void triangle_type(long long A, long long B, long long C);
void validate(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3);
int is_straight_line(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3);
void get_triangle_type(long long A, long long B, long long C);
void translate(long long *x1, long long *y1, long long *x2, long long *y2, long long *x3, long long *y3);
long long get_side(long long x, long long y);

int main(int argc, char **argv){

   /* Check command line args */
    if (argc != 7) {
	fprintf(stderr, "usage: %s six coordinates \n", argv[0]);
	exit(1);
    }

    print_type(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));

}


/* Main routine */
void print_type(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){

validate(x1, y1, x2, y2, x3, y3);
translate(&x1, &y1, &x2, &y2, &x3, &y3);
long long A = get_side(x1, y1);
long long B = get_side(x2, y2);
long long C = get_side(x3, y3);
get_triangle_type(A, B, C);

}

/* Returns a side (borrowed from clukey) */
long long get_side(long long x, long long y){

  return (x*x) + (y*y);
}

/* Prints the triangle_type */
void triangle_type(long long A, long long B, long long C){


  if ((A==B) || (A==C) || (B==C))
  printf("isosceles ");

  else
   printf("scalene ");

  long long rslt = C - B - A;

  if (rslt > 0)
   printf("obtuse\n");

  else if (rslt == 0) 
   printf("right\n");

  else
    printf("acute\n");
  
}


/* Validates the coordinates as describing a triangle */
void validate(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){
 
   if(is_straight_line(x1, y1, x2, y2, x3, y3)){
     printf("not a triangle\n");
     exit(0);
   }
   
}


/* Do coordinates represent a straight line */
int is_straight_line(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){

  return((x1 * (y2 - y3) +
	  x2 * (y3 - y1) +
	  x3 * (y1 - y2)) == 0);
}


/* Get triangle type */
void get_triangle_type(long long A, long long B, long long C){

  if((A > B) && (A > C))
     triangle_type(B, C, A);

  else if ((B > A) && (B > C))
     triangle_type(A, C, B);

  else
     triangle_type(A, B, C);
}




/* This approach was modeled after clukey's */
void translate(long long *x1, long long *y1, long long *x2, long long *y2, long long *x3, long long *y3){

  *x3 = *x3 - *x1;
  *y3 = *y3 - *y1;
  *x2 = *x2 - *x1;
  *y2 = *y2 - *y1;
  *x1 = *x3 - *x2;
  *y1 = *y3 - *y2;
  

}
