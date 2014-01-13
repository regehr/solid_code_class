#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

long double findSide(long double x1, long double y1, long double x2, long double y2 , int debug);

long double readIn(int index , char **argv);

bool eq(long double left , long double right , long double error);

int main(int argc , char *argv[])
{	
	long double error = .00000000001;
	long double error1 = 1.0;
	long double error2 = 0.0001;
	int debug = 0;
	char *NOT = "not a triangle\n";
	if(argc != 7)
	{
		printf(NOT);
		return 0;	
	}

	long double x1 = readIn(1 , argv);
	long double y1 = readIn(2 , argv);
	long double x2 = readIn(3 , argv);
	long double y2 = readIn(4 , argv);
	long double x3 = readIn(5 , argv);
	long double y3 = readIn(6 , argv);

	long double s1 = findSide(x1 , y1 , x2 , y2 , debug);
	long double s2 = findSide(x2 , y2 , x3 , y3 , debug);
	long double s3 = findSide(x3 , y3 , x1 , y1 , debug);

	double angleS1 = acos(((s2 * s2) + (s3 * s3) - (s1 * s1))/(2 * s2 * s3));
    	double angleS2 = acos(((s3 * s3) + (s1 * s1) - (s2 * s2))/(2 * s3 * s1));    
    	double angleS3 = M_PI - angleS1 - angleS2;
	
	if(debug)
	{
		printf("angles = %f , %f , %f, %f\n" , angleS1 , angleS2 , angleS3 , (M_PI/2));
	}
		
	char *toPrint1 = "";
	char *toPrint2 = "";
	
	if(debug)
        {
                printf("side lengths: %Lf, %Lf , %Lf\n", s1 , s2 , s3);
        }	

	if(s1 == 0 || s2 == 0 || s3 == 0)
	{
		printf(NOT);
		return 0;
	}
	else if(eq(s1 + s2 , s3, error) || eq(s1 + s3 , s2 , error) || eq(s2 + s3 , s1 , error))
	{
		printf(NOT);
		return 0;
	}
	else if(s1 == s2 && s2 == s3)
	{
		toPrint1 = "equilateral";
	}
	else if(eq(s1 , s2 , error) || eq(s2 , s3 , error)|| eq(s3 , s1 , error))
	{
		toPrint1 = "isosceles";
	}
	else
	{
		toPrint1 = "scalene";
	}

	if(eq((M_PI / 2) , angleS1 , error) || eq((M_PI / 2) , angleS2 , error) || eq((M_PI / 2) , angleS3 , error))
	{
		toPrint2 = "right";
	}
	else if((angleS1 < ((M_PI / 2) + error2)) && (angleS2 < ((M_PI / 2) + error2)) && (angleS3 < ((M_PI / 2) + error2)))
	{
		toPrint2 = "acute";
	}
	else if((angleS1 > (M_PI / 2)) || (angleS2 > (M_PI / 2)) || (angleS3 > (M_PI / 2)))
	{
		toPrint2 = "obtuse";
	}
	
	printf("%s %s\n" , toPrint1 , toPrint2);
	return 0;
}

long double findSide(long double x1, long double y1, long double x2, long  double y2, int debug)
{
	long double difx = abs(x1 - x2);
	long double dify = abs(y1 - y2);
	
	if(debug)
	{
		printf("difs: %Lf , %Lf\n", difx , dify);
	}

	long double multx = difx * difx;
	long double multy = dify * dify;	
	
	if(debug)
	{
		printf("mults: %Lf , %Lf\n", multx , multy);
	}

	return sqrt(multx + multy);
}

long double readIn(int index , char **argv )
{
	char *temp = argv[index];
	int tempInt = atoi(temp);
	long double toReturn = (long double)tempInt;
	return toReturn;
}

bool eq(long double left , long double right , long double error)
{
	if(left < right)
	{
		return ((right - left) < error);
	}
	else
	{
		return ((left - right) < error);
	}
}
