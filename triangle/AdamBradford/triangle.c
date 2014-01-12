//
//  tri.c
//
//  Created by Adam Bradford on 1/7/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#include <stdio.h>
#include "triangle.h"
#include <math.h>


//private header
long double calc_float_distance_for_points(triangle_point point1, triangle_point point2);
unsigned long long calc_alt_distance_for_points(triangle_point point1, triangle_point point2);
long double calc_angle_for_length(long double c, long double a,long double b);
triangle calculate_triangle_data_for_triangle(triangle t);


//a helper method to make a new triangle point
triangle_point triangle_point_make(unsigned x,unsigned y)
{
	triangle_point point;
	point.x = x;
	point.y = y;
	return point;
}

//returns a new triangle, with all calculations completed for given input points
triangle triangle_for_points(triangle_point point1,triangle_point point2,triangle_point point3)
{
	triangle newTriangle;
	newTriangle.point_1 = point1;
	newTriangle.point_2 = point2;
	newTriangle.point_3 = point3;
	
	newTriangle = calculate_triangle_data_for_triangle(newTriangle);
	return newTriangle;
}

//this calls the methods that calculates both types of lengths and angles
triangle calculate_triangle_data_for_triangle(triangle t)
{
	triangle new_triangle = t;
	new_triangle.length_1 = calc_float_distance_for_points(t.point_2, t.point_3);
	new_triangle.length_2 = calc_float_distance_for_points(t.point_1, t.point_3);
	new_triangle.length_3 = calc_float_distance_for_points(t.point_1, t.point_2);
    
    new_triangle.length_alt_1 = calc_alt_distance_for_points(t.point_2, t.point_3);
	new_triangle.length_alt_2 = calc_alt_distance_for_points(t.point_1, t.point_3);
	new_triangle.length_alt_3 = calc_alt_distance_for_points(t.point_1, t.point_2);
	
	new_triangle.angle_1 = calc_angle_for_length(new_triangle.length_1, new_triangle.length_2, new_triangle.length_3);
	new_triangle.angle_2 = calc_angle_for_length(new_triangle.length_2, new_triangle.length_3, new_triangle.length_1);
	new_triangle.angle_3 = calc_angle_for_length(new_triangle.length_3, new_triangle.length_1, new_triangle.length_2);

	return new_triangle;
}

//returns 0 if the triangle is colinear
int is_triangle(triangle t)
{
	int result = 1;
	if(t.length_1 == t.length_2 + t.length_3 ||
	   t.length_2 == t.length_1 + t.length_3 ||
	   t.length_3 == t.length_1 + t.length_2) result = 0;
	
	return result;
}

//returns 1 if the triangle is acute
int is_acute(triangle t)
{
	int result = 0;
	if(t.angle_1 < 90.0L &&  t.angle_2 < 90.0L && t.angle_3 < 90.0L) result = 1;
	
	return result;
}

//returns 1 if the triangle is obtuse
int is_obtuse(triangle t)
{
	int result = 0;
	if(t.angle_1 > 90.0L ||  t.angle_2 > 90.0L || t.angle_3 > 90.0L) result = 1;
	
	return result;
}

//returns 1 if the triangle is right
int is_right(triangle t)
{
	int result = 0;
	
	unsigned long long a,b,c;
	
	//length 1 is longest
	if(t.length_alt_1 > t.length_alt_2 && t.length_alt_1 > t.length_alt_3)
	{
		c = t.length_alt_1;
		b = t.length_alt_2;
		a = t.length_alt_3;
	}
	//length 2 is longest
	else if(t.length_alt_2 > t.length_alt_1 && t.length_alt_2 > t.length_alt_3)
	{
		c = t.length_alt_2;
		b = t.length_alt_1;
		a = t.length_alt_3;
	}
	//length 3 is longest
	else
	{
		c = t.length_alt_3;
		b = t.length_alt_2;
		a = t.length_alt_1;
	}
    
    //the alt length is the distance formula saved as a long long that
    //doesn't have a sqare root applied so just check pythagoras
	if(a + b == c)result = 1;
	return result;
}

//returns 1 if two alt lenghts are are the same
int is_isosceles(triangle t)
{
	int result = 0;
	
	if(t.length_alt_1 == t.length_alt_2||
	   t.length_alt_2 == t.length_alt_3||
	   t.length_alt_1 == t.length_alt_3) result = 1;

	return result;
}

//returns 1 of the triangle is scalene
int is_scalene(triangle t)
{
	int result = 1;
	
	
	if(t.length_alt_1 == t.length_alt_2 ||
       t.length_alt_1 == t.length_alt_3 ||
	   t.length_alt_2 == t.length_alt_3) result = 0;
	
	return result;
}

//gives a long double distance
long double calc_float_distance_for_points(triangle_point point1, triangle_point point2)
{
	long double x = (long double)point1.x - (long double) point2.x;
	long double y = (long double)point1.y - (long double) point2.y;
	
	long double result = x*x + y*y;
    
	result = sqrtl(result);
	return result;

}

//this calculates the length as a unsigned long long and does not perform the square root
//normally used in the distance formula
unsigned long long calc_alt_distance_for_points(triangle_point point1, triangle_point point2)
{
    long long x = (long long)point1.x - (long long)point2.x;
    long long y = (long long)point1.y - (long long)point2.y;
    
    unsigned long long result = x*x + y*y;
    
    return result;
}

//The law of cosines, the first length is opposite the angle which you wish to find the angle for
long double calc_angle_for_length(long double c, long double a, long double b)
{
	long double result = (a*a + b*b - c*c)/(2.0L*a*b);
	result = acosl(result);
	result = result * 180.0 / M_PI;
	
	return result;
}


