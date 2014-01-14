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

typedef enum{
    ACUTE = 1,
    OBTUSE,
    RIGHT
}triangle_angle_type;

typedef enum{
    SCALENE = 1,
    ISOSCELES,
    EQUILATERAL
}triangle_shape_type;

typedef struct{
	
    triangle_point point_1,point_2,point_3;

    //lengths without the sqrt appled and are not floating point
    unsigned long long length_1,length_2,length_3;
    
    //properties for the triangle
    triangle_angle_type angle_type;
    triangle_shape_type shape_type;
    int is_triangle;

}triangle;

//creates a triangle point
triangle_point triangle_point_make(unsigned x,unsigned y);

int is_colinear(triangle_point p1, triangle_point p2, triangle_point p3);

//returns a triangle with lengths and angles and all properties calculated
triangle triangle_for_points(triangle_point point1,triangle_point point2,triangle_point point3);



#endif
