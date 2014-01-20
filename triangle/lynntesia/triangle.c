#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define error 0.0000001


bool isEqual(double d1, double d2)
{ 
  if(fabs(d1-d2) < error)
    {
      return true;
    }
  return false;
}

bool sameSlope(double x1, double y1, double x2, double y2, double x3, double y3)
{
  return fabs((y1 - y2) * (x1 - x3) - (y1 - y3) * (x1 - x2)) <= error;
}


double lengthOfSide(double x1, double y1, double x2, double y2)
{
  // distance formula 
  double ret;
  double p1, p2;
  p1 = pow((x2-x1), 2);
  p2 = pow((y2-y1), 2);  
  ret = sqrt(p1+p2); 
  return ret;	
   
}

double angleBetween(double s1, double s2, double s3)
{
  double angle = acos((pow(s1, 2)+pow(s2, 2)-pow(s3, 2))/ (pow(s1, 2)*pow(s2, 2)));
  angle = 180*angle/M_PI;
 return angle;  
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

bool isRight(double a1, double a2, double a3)
{
  if(isEqual(a1, 90) || isEqual(a1, 90) || isEqual(a3, 90))
    {
      return true;
    }
  return false;
}

bool isRightPy(double s1, double s2, double s3)
{
  // trying pythagoras theorem for checking right triangle
  double longest = 0;
  double small1 = 0;
  double small2 = 0;
  if(s3 > s2 && s3 > s1)
    {
      longest = s3;
      small1 = s2;
      small2 = s1;
    }
  else if(s2 > s3 && s2 > s1)
    {
      longest = s2;
      small1 = s3;
      small2 = s1;
    }
  else
    {
      longest = s1;
      small1 = s2;
      small2 = s3;
    }
  double p1 = pow(small1, 2);
  double p2 = pow(small2, 2);
  double p3 = pow(longest, 2);
  double sum = p1 + p2;
  if(isEqual(sum, p3))
    {
      return true;
    }
  
  return false;
}

bool isEquilateral(double s1, double s2, double s3)
{
  if(isEqual(s1,s2) && isEqual(s1,s3) && isEqual(s2,s3))
    {
      return true;
    }
  return false;
}



bool isIsosceles(double s1, double s2, double s3)
{
  if(isEqual(s1,s2) && !isEqual(s2,s3) && !isEqual(s1,s3))
    {
      return true;
    }
  else if(isEqual(s1,s3) && !isEqual(s3,s2) && !isEqual(s1,s2))
    {
      return true;
    }
  else if(isEqual(s2,s3) && !isEqual(s3,s1) && !isEqual(s2,s1))
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
  if(!isEqual(s1, s2) && !isEqual(s2, s3) && !isEqual(s1, s3))
    {
      return true;
    }
  return false;
}


int main(int argc, char **argv)
{  
  double xpoints[3];
  double ypoints[3];
  double s1, s2, s3, a1, a2, a3;
  bool scal, iso, equi, acute, obtuse, right; 
  bool collinear;


  // get command line arguments
  if(argc < 7)
    {
      printf("invalid number of coordinates\n");
    }
  else
    {
      xpoints[0] = atoi(argv[1]);
      ypoints[0] = atoi(argv[2]);
      xpoints[1] = atoi(argv[3]);
      ypoints[1] = atoi(argv[4]);
      xpoints[2] = atoi(argv[5]);
      ypoints[2] = atoi(argv[6]);      
    }
  
  // check for nat  
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

    // check for nat: all 3 points lie on the same line
    collinear = sameSlope(xpoints[0], ypoints[0], xpoints[1], ypoints[1], xpoints[2], ypoints[2]);
    if(collinear)
      {
	printf("not a triangle\n");
	return 0;
      }

 
    
  
     //scal, iso, equi, acute, obtuse, right

  s1 = lengthOfSide(xpoints[0], ypoints[0], xpoints[1], ypoints[1]);
  s2 = lengthOfSide(xpoints[2], ypoints[2], xpoints[1], ypoints[1]);
  s3 = lengthOfSide(xpoints[2], ypoints[2], xpoints[0], ypoints[0]); 
 
  scal = isScalene(s1, s2, s3);
  iso = isIsosceles(s1, s2, s3);
  equi = isEquilateral(s1, s2, s3);

  a3 = angleBetween(s1, s2, s3);
  a2 = angleBetween(s1, s3, s2);
  a1 = angleBetween(s2, s3, s1);

  //right = isRight(a1, a2, a3);
  right = isRightPy(s1, s2, s3);
  acute = isAcute(a1, a2, a3);
  obtuse = isObtuse(a1, a2, a3);
 
  
  // (((scalene|isosceles|equilateral) (acute|obtuse|right))|not a triangle)
  if(scal && right)
    {
      printf("scalene right\n");
    }
  else if(scal && obtuse)
    {
      printf("scalene obtuse\n");
    }
  else if(scal && acute)
    {
      printf("scalene acute\n");
    }
  else if(iso && right)
    {
      printf("isosceles right\n");
    }
  else if(iso && obtuse)
    {
      printf("isosceles obtuse\n");
    }
  else if(iso && acute)
    {
      printf("isosceles acute\n");
    }  
  else
    {
      printf("not a triangle\n");
    } 

  return 0;
}


