#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define error 0.00001


double lengthOfSide(double p1x, double p1y, double p2x, double p2y)
{
  // distance formula
  double ret;
  double p1, p2;
  p1 = pow((p2x-p1x), 2);
  p2 = pow((p2y-p1y), 2);
  // printf("%f\n", sqrt(p1+p2));
  ret = sqrt(p1+p2);
  return ret;	
}

double angleBetween(double x1, double y1, double x2, double y2)
{
  double ret, p1, p2, angle;
  p1 = y1-y2;
  p2 = x1-x2;
  angle = atan2(p1, p2);
  ret = angle*180/M_PI;
  return ret;
}

bool isRight(double a1, double a2, double a3)
{
  if((a1 == 90 && a2 < 90 && a3 < 90) ||
     (a2 == 90 && a1 < 90 && a3 < 90) ||
     (a3 == 90 && a1 < 90 && a2 < 90))
    {
      return true;
    }
  return false;
}

bool isObtuse(double a1, double a2, double a3)
{
  if((a1 > 90 && a2 < 90 && a3 < 90) ||
     (a2 > 90 && a1 < 90 && a3 < 90) ||
     (a3 > 90 && a1 < 90 && a2 < 90))
    {
      return true;
    }
  return false;
}

bool isAcute(double a1, double a2, double a3)
{
  if((a1 < 90 && a2 < 90 && a3 < 90) ||
     (a2 < 90 && a1 < 90 && a3 < 90) ||
     (a3 < 90 && a1 < 90 && a2 < 90))
    {
      return true;
    }
  return false;
}

bool isEquilateral(double s1, double s2, double s3)
{
  if(s1 == s2 && s1 == s3 && s2 == s3)
    {
      return true;
    }
  return false;
}

bool isIsosceles(double s1, double s2, double s3)
{
  if(s1 == s2 && s2 != s3 && s1 != s3)
    {
      return true;
    }
  else if(s1 == s3 && s3 != s2 && s1 != s2)
    {
      return true;
    }
  else if(s2 == s3 && s3 != s1 && s2 != s1)
    {
      return true;
    }
  else
    {
      return false;
    }
}

bool isScalene(double s1, double s2, double s3)
{
  if(!isEquilateral(s1, s2, s3) && !isIsosceles(s1, s2, s3))
    {
      return true;
    }
  return false;
}

bool isEqual(double d1, double d2)
{ 
  if(fabs(d1-d2) < error)
    {
      return true;
    }
  return false;
}


int main(int argc, char **argv)
{
  int i ;
  double xpoints[3];
  double ypoints[3];
  double s1, s2, s3, a1, a2, a3;
  bool scal, iso, equi, acute, obtuse, right;


  // get command line arguments
  if(argc < 7)
    {
      printf("invalid number of coordinates\n");
    }
  else
    {
      for(i = 1; i < argc; i+=2)
	{
	  xpoints[i] = atoi(argv[i]);
	  ypoints[i] = atoi(argv[i+1]);
	}          
    }
  
  // check for nat
  /*
  if(isEqual(xpoints[0], xpoints[1]) && isEqual(ypoints[0], ypoints[1]))
    {
      printf("not a triangle\n");
      return 0;
    }
   if(isEqual(xpoints[0], xpoints[2]) && isEqual(ypoints[0], ypoints[2]))
    {
      printf("not a triangle\n");
      return 0;
    }
    if(isEqual(xpoints[2], xpoints[1]) && isEqual(ypoints[2], ypoints[1]))
    {
      printf("not a triangle\n");
      return 0;
    }
  */
  

  s1 = lengthOfSide(xpoints[0], ypoints[0], xpoints[1], ypoints[1]);
  s2 = lengthOfSide(xpoints[2], ypoints[2], xpoints[1], ypoints[1]);
  s3 = lengthOfSide(xpoints[2], ypoints[2], xpoints[0], ypoints[0]);

  printf("%f\n", s1);
  printf("%f\n", s2);
  printf("%f\n", s3);
  
  return 0;
}


