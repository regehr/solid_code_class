#include <limits.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_type(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3);
long long get_side(long long x1, long long x2, long long y1, long long y2);
void triangle_type(long long A, long long B, long long C);
void validate(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3);
int is_straight_line(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3);
void check_in_add_range(long long A, long long B, long long C);



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

check_in_range(x1, y1, x2, y2, x3, y3);
validate(x1, y1, x2, y2, x3, y3);
long long A = get_side(x1, x3, y1, y3);
long long B = get_side(x2, x3, y2, y3);
long long C = get_side(x1, x2, y1, y2);
triangle_type(A, B, C);

}


/* Returns the length of a side */
long long get_side(long long x1, long long x2, long long y1, long long y2){

long long diff_1 = (x2 - x1);
long long diff_2 = (y2 - y1);
long long sq_1 = pow(diff_1, 2);
long long sq_2 = pow(diff_2, 2);
long long sum_of_squares = sq_1 + sq_2;

return sum_of_squares;
}


/* Prints the triangle_type */
void triangle_type(long long A, long long B, long long C){

  char *type = NULL;
  check_in_add_range(A, B, C);

  if((A == B) && (B == C))
  printf("equalateral acute");
 
  else if ((A==B) || (A==C) || (B==C))
  printf("isosceles ");

  else
   printf("scalene ");

  if (((A + B) == C) || ((A + C) == B) || ((B + C) == A))
   printf("right\n");

  else if (((A + B) < C) || ((A + C) < B) || ((B + C) < A)) 
   printf("obtuse\n");

  else
    printf("acute\n");
  
}


/* Validates the coordinates as describing a triangle */
void validate(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){
 
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


/* Do coordinates represent a straight line */
int is_straight_line(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){

  long long denom_1 = abs(y2 - y1);
  long long denom_2 = abs(y3 - y2);
  long long denom_3 = abs(y3 - y1);

  if (denom_1 == 0 || denom_2 == 0 || denom_3 == 0)
    return 0;
 
  long long slope_1 = abs((abs(x2 - x1)) / denom_1);
  long long slope_2 = abs((abs(x3 - x2)) / denom_2);
  long long slope_3 = abs((abs(x3 - x1)) / denom_3);

  return ((slope_1 == slope_2) && (slope_2 == slope_3) && (slope_1 == slope_3));

}


/* Checks for signed overflow */
check_in_range(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){
  
  assert(!(x1 & LLONG_MIN));
  assert(!(y1 & LLONG_MIN));
  assert(!(x2 & LLONG_MIN));
  assert(!(y2 & LLONG_MIN));
  assert(!(x3 & LLONG_MIN));
  assert(!(y3 & LLONG_MIN));

}

/* Checks for signed overflow */
void check_in_add_range(long long A, long long B, long long C){

  assert(!((A+B) & LLONG_MIN));
  assert(!((A+C) & LLONG_MIN));
  assert(!((B+C) & LLONG_MIN));


}
