//
//  triangle_checker.c
//  TraingleTester
//
//  Created by Adam Bradford on 1/7/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#include <stdio.h>
#include "triangle.h"
#include <math.h>


//private header
long double calc_float_distance_for_points(TrianglePoint point1, TrianglePoint point2);
unsigned long long calc_alt_distance_for_points(TrianglePoint point1, TrianglePoint point2);
long double calc_angle_for_length(long double c, long double a,long double b);
Triangle calculate_triangle_data_for_triangle(Triangle triangle);

int compare_numbers(long double num1, long double num2);




TrianglePoint TrianglePointMake(unsigned x,unsigned y)
{
	TrianglePoint point;
	point.x = x;
	point.y = y;
	return point;
}




Triangle triangle_for_points(TrianglePoint point1,TrianglePoint point2,TrianglePoint point3)
{
	Triangle newTriangle;
	newTriangle.point_1 = point1;
	newTriangle.point_2 = point2;
	newTriangle.point_3 = point3;
	
	newTriangle = calculate_triangle_data_for_triangle(newTriangle);
	return newTriangle;
}

Triangle calculate_triangle_data_for_triangle(Triangle triangle)
{
	Triangle newTriangle = triangle;
	newTriangle.length_1 = calc_float_distance_for_points(triangle.point_2, triangle.point_3);
	newTriangle.length_2 = calc_float_distance_for_points(triangle.point_1, triangle.point_3);
	newTriangle.length_3 = calc_float_distance_for_points(triangle.point_1, triangle.point_2);
    
    newTriangle.length_alt_1 = calc_alt_distance_for_points(triangle.point_2, triangle.point_3);
	newTriangle.length_alt_2 = calc_alt_distance_for_points(triangle.point_1, triangle.point_3);
	newTriangle.length_alt_3 = calc_alt_distance_for_points(triangle.point_1, triangle.point_2);
	
	newTriangle.angle_1 = calc_angle_for_length(newTriangle.length_1, newTriangle.length_2, newTriangle.length_3);
	newTriangle.angle_2 = calc_angle_for_length(newTriangle.length_2, newTriangle.length_3, newTriangle.length_1);
	newTriangle.angle_3 = calc_angle_for_length(newTriangle.length_3, newTriangle.length_1, newTriangle.length_2);
	
	
	

	
	// double totalAngle = triangle->angle_1 + triangle->angle_2 + triangle->angle_3;
	return newTriangle;
	

	
}


int is_triangle(Triangle triangle)
{
	int result = 1;
	if(triangle.length_1 == triangle.length_2 + triangle.length_3 ||
	   triangle.length_2 == triangle.length_1 + triangle.length_3 ||
	   triangle.length_3 == triangle.length_1 + triangle.length_2) result = 0;
	
	return result;
}
int is_acute(Triangle triangle)
{
	int result = 0;
	if(triangle.angle_1 < 90.0L &&  triangle.angle_2 < 90.0L && triangle.angle_3 < 90.0L) result = 1;
	
	return result;
}
int is_obtuse(Triangle triangle)
{
	int result = 0;
	if(triangle.angle_1 > 90.0L ||  triangle.angle_2 > 90.0L || triangle.angle_3 > 90.0L) result = 1;
	
	return result;
}
int is_right(Triangle triangle)
{
	int result = 0;
	
	unsigned long long a,b,c;
	
	//case length 1 is longest
	if(triangle.length_alt_1 > triangle.length_alt_2 && triangle.length_alt_1 > triangle.length_alt_3)
	{
		c = triangle.length_alt_1;
		b = triangle.length_alt_2;
		a = triangle.length_alt_3;
	}
	//length 2 is longest
	else if(triangle.length_alt_2 > triangle.length_alt_1 && triangle.length_alt_2 > triangle.length_alt_3)
	{
		c = triangle.length_alt_2;
		b = triangle.length_alt_1;
		a = triangle.length_alt_3;
	}
	//length 3 is longest
	else
	{
		c = triangle.length_alt_3;
		b = triangle.length_alt_2;
		a = triangle.length_alt_1;
	}
	if( a + b == c)result = 1;
	return result;
}

//returns 1 if two lenghts are are the same
int is_isosceles(Triangle triangle)
{
	int result = 0;
	
	if(triangle.length_alt_1 == triangle.length_alt_2||
	   triangle.length_alt_2 == triangle.length_alt_3||
	   triangle.length_alt_1 == triangle.length_alt_3) result = 1;

	return result;
			
	 
}
int is_scalene(Triangle triangle)
{
	int result = 1;
	
	
	if(triangle.length_alt_1 == triangle.length_alt_2 ||
       triangle.length_alt_1 == triangle.length_alt_3 ||
	   triangle.length_alt_2 == triangle.length_alt_3) result = 0;
	
	return result;
}


long double calc_float_distance_for_points(TrianglePoint point1, TrianglePoint point2)
{
	long double x = (long double)point1.x - (long double) point2.x;
	long double y = (long double)point1.y - (long double) point2.y;
	
	long double result = x*x + y*y;
	result = sqrtl(result);
	return result;

}

//this calculates the length as a unsigned long long and removes the sqare route for accuracy
unsigned long long calc_alt_distance_for_points(TrianglePoint point1, TrianglePoint point2)
{
    long long x = (long long)point1.x - (long long)point2.x;
    long long y = (long long)point1.y - (long long)point2.y;
    
    unsigned long long result = x*x + y*y;
    
    return result;
}

//the first length is opposite the angle which you wish to find the angle for
long double calc_angle_for_length(long double c, long double a, long double b)
{
	long double result = (a*a + b*b - c*c)/(2.0L*a*b);
	result = acosl(result);
	result = result * 180.0 / M_PI;
	
	return result;
}


