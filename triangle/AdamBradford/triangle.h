//
//  triangle_checker.h
//  TraingleTester
//
//  Created by Adam Bradford on 1/7/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#ifndef TraingleTester_TriangleChecker_h
#define TraingleTester_TriangleChecker_h

typedef struct
{
	unsigned x,y;
}TrianglePoint;

typedef struct{
	TrianglePoint point_1,point_2,point_3;
	long double angle_1,angle_2,angle_3;
    //lengths calculated as floating point
	long double length_1,length_2,length_3;
    //lengths without the sqrt appled and are not floating point
    unsigned long long length_alt_1,length_alt_2,length_alt_3;
}Triangle;


TrianglePoint TrianglePointMake(unsigned x,unsigned y);
Triangle triangle_for_points(TrianglePoint point1,TrianglePoint point2,TrianglePoint point3);



int is_triangle(Triangle triangle);
int is_acute(Triangle triangle);
int is_obtuse(Triangle triangle);
int is_right(Triangle triangle);
int is_isosceles(Triangle triangle);
int is_scalene(Triangle triangle);





#endif
