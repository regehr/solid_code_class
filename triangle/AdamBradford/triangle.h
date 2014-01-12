//
//  triangle.h
//
//  Created by Adam Bradford on 1/7/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#ifndef triangle_h
#define triangle_h

typedef struct
{
	unsigned x,y;

}triangle_point;

typedef struct{
	
    triangle_point point_1,point_2,point_3;
	long double angle_1,angle_2,angle_3;
    //lengths calculated as floating point
	long double length_1,length_2,length_3;
    //lengths without the sqrt appled and are not floating point
    unsigned long long length_alt_1,length_alt_2,length_alt_3;

}triangle;

//creates a triangle point
triangle_point triangle_point_make(unsigned x,unsigned y);

//returns a triangle with lengths and angles calculated
triangle triangle_for_points(triangle_point point1,triangle_point point2,triangle_point point3);

//these return 1 if true, 0 if false
int is_triangle(triangle t);
int is_acute(triangle t);
int is_obtuse(triangle t);
int is_right(triangle t);
int is_isosceles(triangle t);
int is_scalene(triangle t);

#endif
