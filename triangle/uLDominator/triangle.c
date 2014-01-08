/*
============================================================================

The analyzer takes six command line arguments. The first two are
respectively the x and y coordinates of the first point of the
triangle, the second two are respectively the x and y coordinates of
the second point, etc. Each coordinate is a decimal integer in the
range 0...INT_MAX (inclusive) where INT_MAX comes from limits.h on a
32-bit or 64-bit Linux machine.

The behavior of the triangle analyzer is undefined if the input format
does not match the one specified above.

The output of the triangle analyzer is a single line of text that is
terminated by a newline. This line is the result of the analysis of
the triangle and it should match the following (informal) regular
expression:

(("scalene"|"isosceles"|"equilateral") ("acute"|"right"|"obtuse")) | "not a triangle"

Non-functional requirement:

- The analyzer must be written in C that can be compiled by GCC on a
  CADE Lab Linux machine

Turn in your analyzer like this:

- push it to a directory in the class github repo called
  "triangle/username" where "username" is your github user name

- include a makefile so that when someone types "make" in your
  triangle directory, the result is an executable called "triangle"

============================================================================
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Point
{
	int x;
	int y;
};

//Calculate the distance between two given points
double distance(struct Point p1, struct Point p2)
{
	double dist;
	int x, y;
	
	x = abs(p1.x - p2.x);
	y = abs(p1.y - p2.y);

	dist = sqrt(x*x + y*y);
	
	return dist;
}


double angle(double d1, double d2, double d3)
{
	double angle;
	angle = acos((d2*d2 + d3*d3 - d1*d1)/(2*d2*d3));
	return angle*(180.0/M_PI);
}

int main(int argc, char* argv[])
{
	//Local vars
	struct Point p1, p2, p3;
	float angle1, angle2, angle3;
	double distance1, distance2, distance3;
	char* result;

	//Parse command line input
	p1.x = atoi(argv[1]); p1.y = atoi(argv[2]);
	p2.x = atoi(argv[3]); p2.y = atoi(argv[4]);
	p3.x = atoi(argv[5]); p3.y = atoi(argv[6]);
	
	//Determine length of each side
	distance1 = distance(p1, p2); //adjacent
	distance2 = distance(p2, p3); //opposite
	distance3 = distance(p3, p1); //hypotenuse
	
	//Determine angles between sides
	angle1 = angle(distance1, distance2, distance3);
	angle2 = angle(distance2, distance1, distance3);
	angle3 = angle(distance3, distance1, distance2);
	
	//Triangle check cases
	//NOT A TRIANGLE case
	if(!(distance1 < distance2+distance3) || !(distance2 < distance1+distance3) || !(distance3 < distance1+distance2))
	{
		result = "not a triangle\n";
	}
	//EQUILATERAL case
	else if(distance1 == distance2 && distance2 == distance3)
	{
		//Impossible to have anything but acute angles
		result = "equilateral acute\n";
	}
	//ISOSCELES case
	else if((distance1 == distance2) || (distance2 == distance3) || (distance3 == distance1))
	{
		result = "isoscelese";
		
		//Determine type of angles
		if((angle1 > 90.0) || (angle2 > 90.0) || (angle3 > 90.0))
			result += " obtuse\n";
		else if((angle1 == 90.0) || (angle2 == 90.0) || (angle3 == 90.0))
			result = " right\n";
		else
			result = " acute\n";
	}
	//SCALENE case
	else
	{
		result = "scalene";
		
		//Determine type of angles
		if((angle1 > 90.0) || (angle2 > 90.0) || (angle3 > 90.0))
			result = " obtuse\n";
		else if((angle1 == 45.0) || (angle2 == 45.0) || (angle3 == 45.0))
			result = " right\n";
		else
			result = " acute\n";
	}
	
	//Print the results
	printf(result);
	
	return(0);
}
