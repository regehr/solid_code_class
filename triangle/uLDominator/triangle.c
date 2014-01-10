#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Associate two ints as an xy pair
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

//Determine the angle using the law of cosines
double angle(double d1, double d2, double d3)
{
	double angle;
	angle = acos((d2*d2 + d3*d3 - d1*d1)/(2*d2*d3));
	return angle*(180.0/M_PI);
}

//Determine if any of the given angles are obtuse
int is_obtuse(double a1, double a2, double a3)
{
	if((a1 > 90.0) || (a2 > 90.0) || (a3 > 90.0))
		return 1;	
	return 0;
}

//Determine if any of the given angles are right
int is_right(double a1, double a2, double a3)
{
	if((a1 == 90.0) || (a2 == 90.0) || (a3 == 90.0))
		return 1;
	return 0;
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
	//ISOSCELES case
	else if((distance1 == distance2) || (distance2 == distance3) || (distance3 == distance1))
	{
		//Determine type of angles
		if(is_right(angle1, angle2, angle3))
			result = "isoscelese right\n";
		else if(is_obtuse(angle1, angle2, angle3))
			result = "isoscelese obtuse\n";
		else
			result = "isoscelese acute\n";
	}
	//SCALENE case
	else
	{
		//Determine type of angles
		if(is_right(angle1, angle2, angle3))
			result = "scalene right\n";
		else if(is_obtuse(angle1, angle2, angle3))
			result = "scalene obtuse\n";
		else
			result = "scalene acute\n";
	}
	
	//Print the results
	printf(result);
	
	return(0);
}
