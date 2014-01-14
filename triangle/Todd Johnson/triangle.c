//Todd Johnson, u0714702, CS 5959

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define error 0.000001

/*
 * Represent a point with x, y coordinates
 */
struct Point
{
  double x;
  double y;
};

/*
 * Distance formula using points to find side lengths
 */
double distance(struct Point p1, struct Point p2)
{
  return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}


int point_equals(struct Point p1, struct Point p2)
{
  if(p1.x == p2.x && p1.y == p2.y)
    return 1;
  else
    return 0;
}

/*
 * Convert radians to degrees
 */
double radians_to_degrees(double rad)
{
  return ((180 * rad)/M_PI);
}


/*
 * Taken from class repo for error handling trying 
 * to get equilateral test case to work.
 */
double error_tolerance(double a, double b)
{
  if (a > b)
    return (a- b) < error;
  else
    return (b-a) < error;
}

int main(int argc, char* argv[])
{

  //3 input points 
  struct Point p1;
  struct Point p2;
  struct Point p3;

  //3 sides and 3 angles
  double side_a;
  double side_b;
  double side_c;
  double angle_A;
  double angle_B;
  double angle_C;

  //Check for valid number of arguments
  if(argc < 7)
    {
      printf("Invalid arguments\n");
      return 0;
    }

  //Get x, y coordinate cmd arguments
  p1.x = atoi(argv[1]);
  p1.y = atoi(argv[2]);
  p2.x = atoi(argv[3]);
  p2.y = atoi(argv[4]);
  p3.x = atoi(argv[5]);
  p3.y = atoi(argv[6]);

  if(point_equals(p1, p2) || point_equals(p2, p3) || point_equals(p1, p3))
    {
      printf("not a triangle\n");
      return 0;
    }

  //Use points to get triangle's sides
  side_a = distance(p1, p2);
  side_b = distance(p1, p3);
  side_c = distance(p2, p3);

  //printf("%f, %f, %f\n", side_a, side_b, side_c);

  //Use triangle's sides to find its Angles
  //Cosine Rule
  angle_C = acos(((pow(side_a, 2)+ pow(side_b, 2) - pow(side_c, 2))/(2*side_a*side_b)));
  angle_C = radians_to_degrees(angle_C);
  //Sine rule to find second angle
  angle_B = acos(((pow(side_a, 2)+ pow(side_c, 2) - pow(side_b, 2))/(2*side_a*side_c)));
  angle_B = radians_to_degrees(angle_B);
  //Use sum of angles to find third angle
  angle_A = 180 - angle_C - angle_B;

  //Side Conditions and final print statements
  if(error_tolerance(side_a , side_b) && error_tolerance(side_a, side_c) && error_tolerance(side_b, side_c))
    printf("equilateral ");
  else if(error_tolerance(side_a , side_b) || error_tolerance(side_a, side_c) || error_tolerance(side_b, side_c))
    printf("isosceles ");
  else
    printf("scalene ");
  
  //printf("%f, %f, %f\n", angle_A, angle_B, angle_C);
  //Right angle check
  if(error_tolerance(angle_A, 90) || error_tolerance(angle_B, 90) || error_tolerance(angle_C, 90))
    printf("right\n");
  //Obtuse angle check
  else if(angle_A > 90 || angle_B > 90 || angle_C > 90)
    printf("obtuse\n");
  //Acute
  else
    printf("acute\n");


  return 0;
}

