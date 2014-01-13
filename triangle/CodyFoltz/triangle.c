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

#define NOT_TRIANGLE "not a triangle"
#define EQUILATERAL "equilateral"
#define ISOSCELES "isosceles"
#define SCALENE "scalene"
#define ACUTE "acute"
#define RIGHT "right"
#define OBTUSE "obtuse"

/**
 * 
 * ((sc|is|eq|) (ac|ri|ob)) | (not a triangle)
 * 
 * 
 */



typedef struct point{
    double x;
    double y;
}Point;

typedef struct slope{
    int is_negative;
        int rise;
        int run;
    } Slope;

char* find_triangle_type(Point point1, Point point2, Point point3);
Point create_point(char* x, char* y);
double calculate_distance(Point point1, Point point2);
int is_legal_triangle(Point point1, Point point2, Point point3);
void insure_correct_slope(Slope* slope);
Slope calculate_slope(Point pointA, Point pointB);
int are_slopes_equal(Slope slopeA, Slope slopeB);
int are_points_equal(Point pointA, Point pointB);
int check_for_overlapping_points(Point pointA, Point pointB, Point pointC);

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
        return NOT_TRIANGLE;
    }
    
    double side_1_2 = calculate_distance(point1, point2);
    double side_1_3 = calculate_distance(point1, point3);
    double side_2_3 = calculate_distance(point2, point3);
    
    //check for equalateral
    if(side_1_2 == side_1_3 && side_1_2 == side_2_3){
        return "equilateral acute";
    }
    
    return NOT_TRIANGLE;
    
    
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

/**
 * Checks that the 3 given points makes a valid triangle.  Returns 0 when the
 * triangle contains duplicate points or the 3 points make a straight line. 
 * @param point1
 * @param point2
 * @param point3
 * @return 
 */
int is_legal_triangle(Point point1, Point point2, Point point3){
    
    //Overlapping points are illegal
    if(has_overlapping_points(point1, point2, point3)){
        return 0;
    }
    
    /* rise/run */
    Slope slope_1_2 = calculate_slope(point1, point2);
    Slope slope_1_3 = calculate_slope(point1, point3);
    
    //Equal slopes means all 3 points form one straight line.
    return !are_slopes_equal(slope_1_2, slope_1_3);
}

Slope calculate_slope(Point pointA, Point pointB){
    Slope slope;
    slope.rise = pointA.y - pointB.y;
    slope.run = pointA.x - pointB.x;
    insure_correct_slope(&slope);
    return slope;
}

void insure_correct_slope(Slope* slope){
    if(slope->rise < 0 || slope->run < 0){
        slope->is_negative = 1;
        slope->rise = abs(slope->rise);
        slope.run = abs(slope->run);
    } else if( slope->rise >= 0 && slope->run >= 0){
        slope->is_negative = 1;
    } else {
        slope->is_negative = -1;
    }
}

int are_slopes_equal(Slope slopeA, Slope slopeB){
    return (slopeA.is_negative == slopeB.is_negative) && (slopeA.rise == slopeB.rise) && (slopeA.run == slopeB.run);
}

int are_points_equal(Point pointA, Point pointB){
    return (pointA.x == pointB.x) && (pointA.y = pointB.y);
}

int has_overlapping_points(Point pointA, Point pointB, Point pointC){
    if(are_points_equal(pointA, pointB)){
        return 1;
    }
    
    if(are_points_equal(pointA, pointC)){
        return 1;
    }
    
    if(are_points_equal(pointB, pointC)){
        return 1;
    }
    
    return 0;
}



/*
 * Dot product = p1.x * p2.x + p1.y * p2.y
 * 
 * 
 * If the dot product of A and B is greater than zero, then we know the angle is
 * less than 90 degrees. If the dot product is equal to zero then we know the 
 * two vectors are perpendicular or orthogonal to one another. If the scalar 
 * value returned is less than zero, we know the angle is greater than 90 
 * degrees. If you need the actual angle between the two vectors, 
 * take the inverse cosine of the scalar value returned by the dot product.
 */
