#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long double findSide(long double x1, long double y1, long double x2, long double y2);

long double readIn(int index , char **argv);

int main(int argc , char *argv[])
{
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

	long double s1 = findSide(x1 , y1 , x2 , y2);
	long double s2 = findSide(x2 , y2 , x3 , y3);
	long double s3 = findSide(x3 , y3 , x1 , y1);

	double angleS1 = acos(((s2 * s2) + (s3 * s3) - (s1 * s1))/(2 * s2 * s3));
    	double angleS2 = acos(((s3 * s3) + (s1 * s1) - (s2 * s2))/(2 * s3 * s1));    
    	double angleS3 = M_PI - angleS1 - angleS2;
	
	char *toPrint1 = "";
	char *toPrint2 = "";

	if(s1 == 0 || s2 == 0 || s3 == 0)
	{
		printf(NOT);
		return 0;
	}
	else if(((s1 + s2) == s3) || ((s1 + s3 == s2) || ((s2 + s3) == s1)))
	{
		printf(NOT);
		return 0;
	}
	else if(s1 == s2 && s2 == s3)
	{
		toPrint1 = "equilateral";
	}
	else if(s1 == s2 || s2 == s3 || s3 == s1)
	{
		toPrint1 = "isosceles";
	}
	else
	{
		toPrint1 = "scalene";
	}

	if((s1 < (M_PI / 2)) && (s2 < (M_PI / 2)) && (s3 < (M_PI / 2)))
	{
		toPrint2 = "acute";
	}
	else if((s1 > (M_PI / 2)) || (s2 > (M_PI / 2)) || (s3 > (M_PI / 2)))
	{
		toPrint2 = "obtuse";
	}
	else
	{
		toPrint2 = "right";
	}
	
	printf("side lengths: %Lf, %Lf , %Lf\n", s1 , s2 , s3);
	printf("%s %s\n" , toPrint1 , toPrint2);
}

long double findSide(long double x1, long double y1, long double x2, long  double y2)
{
	long double difx = abs(x1 - x2);
	long double dify = abs(y1 - y2);

	printf("difs: %Lf , %Lf\n", difx , dify);

	long double multx = difx * difx;
	long double multy = dify * dify;	

	printf("mults: %Lf , %Lf\n", multx , multy);

	return sqrt(multx + multy);
}

long double readIn(int index , char **argv)
{
	char *temp = argv[index];
	int tempInt = atoi(temp);
	long double toReturn = (long double)tempInt;
	return toReturn;
}
