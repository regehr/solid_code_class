/* 
 * File:   main.c
 * Author: codyfoltz
 * 
 * 
 * 
 * 
 * Created on January 8, 2014, 8:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct point{
    double x;
    double y;
}Point;

char* find_triangle_type(Point point1, Point point2, Point point3);
Point create_point(char* x, char* y);
double calculate_distance(Point point1, Point point2);
int is_legal_triangle(Point point1, Point point2, Point point3);

/*
 * 
 */
int main(int argc, char** argv) {
    
//    if(argc != 7){
//        printf("not a triangle");
//        return 0;
//    }
    
    Point point1 = create_point(argv[3], argv[4]);
    Point point2 = create_point(argv[1], argv[2]);
    Point point3 = create_point(argv[5], argv[6]);
    
    char* triangle_type = find_triangle_type(point1, point2, point3);
    
    printf("%s", triangle_type);

    return (EXIT_SUCCESS);
}

/**
 * Figures out the type of triangle and then reports the type
 * @param point1
 * @param point2
 * @param point3
 * @return A string of the type of triangle
 */
char* find_triangle_type(Point point1, Point point2, Point point3)
{   
    if(is_legal_triangle(point1, point2, point3)){
        return "not a triangle";
    }
    
    double side_1_2 = calculate_distance(point1, point2);
    double side_1_3 = calculate_distance(point1, point3);
    double side_2_3 = calculate_distance(point2, point3);
    
    //check for equalateral
    if(side_1_2 == side_1_3 && side_1_2 == side_2_3){
        return "acute equilateral";
    }
    
    return "not a triangle";
    
    
}

/**
 * Creates a point "object" from an x and y string.
 * @param x
 * @param y
 * @return 
 */
Point create_point(char* x, char* y)
{
    Point point;
    
    point.x = atoi(x);
    point.y = atoi(y);
    return point;
}

/**
 * Calculates the distance between 2 points.
 * @param point1
 * @param point2
 * @return 
 */
double calculate_distance(Point point1, Point point2)
{
    double side = 0;
    
    //distance formula = sqrt( (x2^2-x1^2) + (y2^2 - y1^2) )
    
    double x_side = point2.x * point2.x - point1.x * point1.x;
    double y_side = point2.y * point2.y - point1.y * point1.y;
    double total = x_side + y_side;
    
    side = sqrt( total );
    
    return side;
}
int is_legal_triangle(Point point1, Point point2, Point point3){
    int is_legal_triangle = 0;
    
    return is_legal_triangle;
    
}


