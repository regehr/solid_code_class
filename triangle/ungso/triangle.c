#include <limits.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_type(int x1, int y1, int x2, int y2, int x3, int y3);
void check_in_range(int x1, int y1, int x2, int y2, int x3, int y3);
double get_side(double x1, double x2, double y1, double y2, int length);
void triangle_type(double A_len, double B_len, double C_len, double A, double B, double C);
void validate(int x1, int y1, int x2, int y2, int x3, int y3);


int main(int argc, char **argv){

   /* Check command line args */
    if (argc != 7) {
	fprintf(stderr, "usage: %s six coordinates \n", argv[0]);
	exit(1);
    }

    print_type(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));

}


/* Main routine */
void print_type(int x1, int y1, int x2, int y2, int x3, int y3){

  /* first check in range */
check_in_range(x1, y1, x2, y2, x3, y3);
validate(x1, y1, x2, y2, x3, y3);
double A_len = get_side((double)x1, (double)x3, (double)y1, (double)y3, 1);
double B_len = get_side((double)x2, (double)x3, (double)y2, (double)y3, 1);
double C_len = get_side((double)x1, (double)x2, (double)y1, (double)y2, 1);

double A = get_side((double)x1, (double)x3, (double)y1, (double)y3, 0);
double B = get_side((double)x2, (double)x3, (double)y2, (double)y3, 0);
double C = get_side((double)x1, (double)x2, (double)y1, (double)y2, 0); 
triangle_type(A_len, B_len, C_len, A, B, C);

}

/* Returns the length of a side */
double get_side(double x1, double x2, double y1, double y2, int length){

double diff_1 = (x2 - x1);
double diff_2 = (y2 - y1);
double sq_1 = pow(diff_1, 2);
double sq_2 = pow(diff_2, 2);
double sum_of_squares = sq_1 + sq_2;
if(length)
   return sqrt(sum_of_squares);

else
   return sum_of_squares;
}


/* Prints the triangle_type */
void triangle_type(double A_len, double B_len, double C_len, double A, double B, double C){

  char *type = NULL;

  if((A_len == B_len) && (B_len == C_len))
  printf("equalateral acute");
 
  else if ((A==B) || (A==C) || (B==C))
  printf("isosceles ");

  else
   printf("scalene ");

  if ((A + B) == C || (A + C) == B || (B + C) == A)
   printf("right\n");

  else if ((A + B) < C || (A + C) < B || (B + C) < A) 
   printf("obstuse\n");

  else
    printf("acute\n");
  
}

/* Checks that x is in range 0 ... 2^31 -1 assuming no negative ints are allowed */
void check_in_range(int x1, int y1, int x2, int y2, int x3, int y3){

assert(!(x1 & INT_MIN));
assert(!(y1 & INT_MIN));
assert(!(x2 & INT_MIN));
assert(!(y2 & INT_MIN));
assert(!(x3 & INT_MIN));
assert(!(y3 & INT_MIN));


}

/* validates the coordinates as describing a triangle */
void validate(int x1, int y1, int x2, int y2, int x3, int y3){
 
  int invalid = 0;

if(((x1 == x2) && (y1 == y2)))
   invalid = 1;

else if (((x2 == x3) && (y2 == y3)))
   invalid = 1;

else if (((x1 == x3) && (y1 == y3)))
   invalid = 1;

 if(!invalid)
 if(is_straight_line(x1, y1, x2, y2, x3, y3))
   invalid = 1;

 if (invalid){
     printf("not a triangle\n");
     exit(0);
 }
   
}

/* Do coordinates represent a straight line, i.e, not a triangle? */
int is_straight_line(int x1, int y1, int x2, int y2, int x3, int y3){

  int denom_1 = abs(y2 - y1);
  int denom_2 = abs(y3 - y2);
  int denom_3 = abs(y3 - y1);
  if (denom_1 == 0 || denom_2 == 0 || denom_3 == 0)
    return 0;
  if (denom_1 == INT_MIN || denom_2 == INT_MIN || denom_3 == INT_MIN)
    return 0;
  double slope_1 = abs((abs(x2 - x1)) / denom_1);
  double slope_2 = abs((abs(x3 - x2)) / denom_2);
  double slope_3 = abs((abs(x3 - x1)) / denom_3);

  return ((slope_1 == slope_2) && (slope_2 == slope_3) && (slope_1 == slope_3));

}
