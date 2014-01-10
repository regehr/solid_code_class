#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

double checkCollinearity(int* P1, int* P2, int* P3);
double computeSide(int* P1, int* P2);
void checkTriangle(int* P1, int* P2, int* P3);
void checkAngles(double S1, double S2, double S3, char* result);
bool closeEnough(double firstValue, double secondValue);

int main(int argc, char* argv[])
{

  //assign the args
  int *P1 = malloc(2*sizeof(int));
  int *P2 = malloc(2*sizeof(int));
  int *P3 = malloc(2*sizeof(int));

  P1[0] = atoi(argv[1]);
  P1[1] = atoi(argv[2]);

  P2[0] = atoi(argv[3]);
  P2[1] = atoi(argv[4]);

  P3[0] = atoi(argv[5]);
  P3[1] = atoi(argv[6]);
  
  //check to see if the points form a triangle
  double det = checkCollinearity(P1, P2, P3);

  if(det == 0)
    {
      printf("Not a triangle\n");
      exit(1);
    }

  //check for the type of triangle scalene, isosceles, or equilateral
  checkTriangle(P1, P2, P3);

  //check the angles to determine obtuse, actuce, or right

  free(P1);
  free(P2);
  free(P3);

}

void checkTriangle(int* P1, int* P2, int* P3)
{
  char* result = "";

  //compute the length of each side
  double S1 = computeSide(P1, P2);
  double S2 = computeSide(P2, P3);
  double S3 = computeSide(P1, P3);

  //if they're all the same
  if(S1 == S2 && S1 == S3 && S2 == S3)
    {
      result = "equilateral ";
    }
  //if two are the same
  else if(S1 == S2 || S1 == S3 || S2 == S3)
    {
      result = "isosceles ";
    }
  //if they're all different
  else
    {
      result = "scalene ";
    }

  checkAngles(S1, S2, S3, result);
}

/*
  Computes and checks the angles of the triangle and outputs
  Right
  Obtuse
  Acute
 */
void checkAngles(double a, double b, double c, char* result)
{
  double ninteyDegrees = M_PI/2;

  //compute the angles
  double A = acos((-pow(a, 2) + pow(b, 2) + pow(c, 2))/(2*b*c));
  double B = acos((pow(a, 2) - pow(b, 2) + pow(c, 2))/(2*a*c));
  double C = acos((pow(a, 2) + pow(b, 2) - pow(c, 2))/(2*a*b));

  //if one of them is 90 degrees
  if(closeEnough(A, ninteyDegrees) || closeEnough(B, ninteyDegrees) || closeEnough(C, ninteyDegrees))
    {
      printf("right\n");
    }
  //if one of them is over 90 degrees
  else if (A > ninteyDegrees || B > ninteyDegrees || C > ninteyDegrees)
    {
      printf("%sobtuse\n", result);
    }
  else if (A < ninteyDegrees && B < ninteyDegrees && C < ninteyDegrees)
    {
      printf("%sacute\n", result);
    }
}

/*
  Check the area of the triangle formed by the points
*/
double checkCollinearity(int* P1, int* P2, int* P3)
{
  return (P1[0]*P2[1]*1 - P1[0]*1*P3[1] - P1[1]*P2[0]*1 + P1[1]*1*P3[1] + 1*P2[0]*P3[1] - 1*P2[1]*P3[0])/2;
}

/*
  Computes the length of one of the line formed by P1 and P2
 */
double computeSide(int* P1, int* P2)
{
  return sqrt(pow(P2[0] - P1[0], 2) + pow (P2[1] - P1[1], 2));
}

/*
  Checks two doubles for equality up to six significant digits
*/
bool closeEnough(double firstValue, double secondValue)
{
  int firstRounded = firstValue*1000000;
  int secondRounded = secondValue*1000000;

  if(firstRounded == secondRounded)
    {
      return true;
    }
  else
    {
      return false;
    }
}
