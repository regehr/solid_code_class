//
//  triangle.c
//
//  Created by Adam Bradford on 1/7/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "triangle.h"



//Method Declarations
triangle calculate_triangle_data_for_triangle(triangle t);
unsigned long long calc_distance_for_points(triangle_point point1, triangle_point point2);
triangle_angle_type angle_type_for_triangle(triangle t);
triangle_shape_type shape_type_for_triangle(triangle t);
int is_triangle(triangle t);
int is_colinear(triangle_point p1, triangle_point p2, triangle_point p3);
int descending_compare_long_long (const void * a, const void * b);


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
	
	
	//compute lengths.  these will not have the square root applied and are not FP
	new_triangle.length_1 = calc_distance_for_points(t.point_2, t.point_3);
	new_triangle.length_2 = calc_distance_for_points(t.point_1, t.point_3);
	new_triangle.length_3 = calc_distance_for_points(t.point_1, t.point_2);
	
	
	//Calculate properties
	new_triangle.is_triangle = is_triangle(new_triangle);
	new_triangle.angle_type = angle_type_for_triangle(new_triangle);
	new_triangle.shape_type = shape_type_for_triangle(new_triangle);
	
	return new_triangle;
}

triangle_angle_type angle_type_for_triangle(triangle t)
{
	
	//add lengths of triangle to array
	unsigned long long lengths[3];
	lengths[0] = t.length_1;
	lengths[1] = t.length_2;
	lengths[2] = t.length_3;
	
	//sort them from largest to smallest
	qsort(lengths, 3, sizeof(unsigned long long), descending_compare_long_long);
	
	int result = RIGHT;
	
	//the alt length is the distance formula saved as a long long that
	//doesn't have a sqare root applied so just check pythagoras
	
	if(lengths[0] <  lengths[1] + lengths[2]) result = ACUTE;
	else if(lengths[0] >  lengths[1] + lengths[2])result = OBTUSE;
	
	return result;
}
triangle_shape_type shape_type_for_triangle(triangle t)
{
	int result = SCALENE;
	
	if(t.length_1 == t.length_2 ||
	   t.length_1 == t.length_3 ||
	   t.length_2 == t.length_3) result = ISOSCELES;
	
	if(t.length_1 == t.length_2 &&
	   t.length_1 == t.length_3 &&
	   t.length_2 == t.length_3) result = EQUILATERAL;
	
	return result;
}

//returns 0 if the triangle is colinear
int is_triangle(triangle t)
{
	int result = !is_colinear(t.point_1, t.point_2, t.point_3);
	
	return result;
}

int is_colinear(triangle_point p1, triangle_point p2, triangle_point p3)
{
	//this checks if the area is 0
	//see http://demonstrations.wolfram.com/TheAreaOfATriangleUsingADeterminant/
	long long calc1 = ((long long)p1.y - (long long)p2.y) * ((long long)p1.x - (long long)p3.x);
	long long calc2 = ((long long)p1.y - (long long)p3.y) * ((long long)p1.x - (long long)p2.x);
	int result = (calc1 == calc2);
	return result;
}



//this calculates the length as a unsigned long long and does not perform the square root
//normally used in the distance formula and for calculating the properties of the triangle
unsigned long long calc_distance_for_points(triangle_point point1, triangle_point point2)
{
	long long x = (long long)point1.x - (long long)point2.x;
	long long y = (long long)point1.y - (long long)point2.y;
	
	unsigned long long result = x*x + y*y;
	
	return result;
}

int descending_compare_long_long (const void * a, const void * b)
{
	int result = 1;
	if ( *(unsigned long long*)a >  *(unsigned long long*)b ) result = -1;
	else if ( *(unsigned long long*)a == *(unsigned long long*)b ) result = 0;
	else if ( *(unsigned long long*)a <  *(unsigned long long*)b ) result = 1;
	
	return result;
}



