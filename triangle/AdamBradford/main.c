//
//  main.c
//  c_triangle_checker
//
//  Created by Adam Bradford on 1/11/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "triangle.h"
#include <assert.h>

char * acute_obutse_or_right_string_for_triangle(triangle triangle);
char * scalene_iso_string_for_triangle(triangle triangle);

int main(int argc, const char * argv[])
{

    triangle_point points[3];
    int i;
    
    //do we even have inputs?
    for( i = 0; i < 7; i++)
    {
        if(!argv[i])return -1;
    }
    
    /* parse the points */
    points[0] = triangle_point_make(atoi(argv[1]),atoi(argv[2]));
    points[1] = triangle_point_make(atoi(argv[3]),atoi(argv[4]));
    points[2] = triangle_point_make(atoi(argv[5]),atoi(argv[6]));

    
    //make the triangle!
    triangle triangle = triangle_for_points(points[0], points[1], points[2]);
    
    //output?
    if(!is_triangle(triangle))
    {
        printf("not a triangle\n");
    }
    else
    {
        char *angle = acute_obutse_or_right_string_for_triangle(triangle);
        char *type = scalene_iso_string_for_triangle(triangle);
        
        printf("%s %s\n",type,angle);
    }
    return 0;
}

char * acute_obutse_or_right_string_for_triangle(triangle triangle)
{
    char *result;
    
    int right,acute,obtuse;
    right = is_right(triangle);
    acute = is_acute(triangle);
    obtuse = is_obtuse(triangle);
    
    assert(acute != obtuse);

    if(right) result = "right";
    else if(acute) result = "acute";
    else result = "obtuse";
    
    return result;
    
}

char * scalene_iso_string_for_triangle(triangle triangle)
{
    char *result;
    
    int scalene,iso;
   
    scalene = is_scalene(triangle);
    iso = is_isosceles(triangle);
    
    assert(scalene != iso);
    
    if(scalene) result = "scalene";
    else result = "isosceles";
    
    return result;
}

