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
#define EQUILATERAL_ACUTE "equilateral acute"
#define ISOSCELES_ACUTE "isosceles acute"
#define ISOSCELES_OBTUSE "isosceles obtuse"
#define ISOSCELES_RIGHT "isosceles right"
#define SCALENE_ACUTE "scalene acute"
#define SCALENE_OBTUSE "scalene obtuse"
#define SCALENE_RIGHT "scalene right"



/**
 * 
 * ((sc|is|eq|) (ac|ri|ob)) | (not a triangle)
 * 
 * 
 */

typedef enum {sc, is, eq} triangle_side_type;
typedef enum {ac, ri, ob} triangle_angle_type;

typedef struct point{
    long long x;
    long long y;
}Point;

typedef struct slope{
    int is_negative;
        int rise;
        int run;
    } Slope;

char* find_triangle_type(Point points[]);
Point create_point(char* x, char* y);
long long calculate_squared_distance(Point point1, Point point2);
int is_illegal_triangle(Point point1, Point point2, Point point3);
void insure_correct_slope(Slope* slope);
Slope calculate_slope(Point pointA, Point pointB);
int are_slopes_equal(Slope slopeA, Slope slopeB);
int are_points_equal(Point pointA, Point pointB);
int check_for_overlapping_points(Point pointA, Point pointB, Point pointC);
triangle_side_type find_triangle_side_type(long long sides[]);
triangle_angle_type find_triangle_angle_type(long long angles[]);
int gcd(long long a, long long b);
void reduce_slope(Slope* slope);
int dot_product(Point point_A, Point point_B, Point origin);
long long get_angle_type();
char* triangle_classification(long long sides[], long long angles[]);

/*
 * 
 */
int main(int argc, char** argv) {
    
//    if(argc != 7){
//        printf("not a triangle");
//        return 0;
//    }
    
    Point points[3];
    points[0] = create_point(argv[1], argv[2]);
    points[1] = create_point(argv[3], argv[4]);
    points[2] = create_point(argv[5], argv[6]);
    
    char* triangle_type = find_triangle_type(points);
    
    printf("%s\n", triangle_type);

    return (EXIT_SUCCESS);
}

int cmpfunc (const void * a, const void * b)
{
   return ( *(long long*)a - *(long long*)b );
}

/**
 * Figures out the type of triangle and then reports the type
 * @param point1
 * @param point2
 * @param point3
 * @return A string of the type of triangle
 */
char* find_triangle_type(Point points[])
{   
    if(is_illegal_triangle(points[0], points[1], points[2])){
        return NOT_TRIANGLE;
    }
    long long  sides[3];
    long long dot_product_angles[3];
    
    sides[0] = calculate_squared_distance(points[0], points[1]);
    sides[1] = calculate_squared_distance(points[0], points[2]);
    sides[2] = calculate_squared_distance(points[1], points[2]);
    
    dot_product_angles[0] = dot_product(points[0], points[1], points[2]);
    dot_product_angles[1] = dot_product(points[1], points[2], points[0]);
    dot_product_angles[2] = dot_product(points[2], points[0], points[1]);
    
    qsort(sides, 3, sizeof(long long), cmpfunc);
    qsort(dot_product_angles, 3, sizeof(long long), cmpfunc);
    
    return triangle_classification(sides, dot_product_angles);

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
long long calculate_squared_distance(Point point1, Point point2)
{
    long long side = 0;
    //distance formula = sqrt( (x2-x1)^2 + (y2 - y1) )
    long long x_side = point2.x - point1.x;
    x_side = x_side * x_side;
    long long y_side = point2.y - point1.y;
    y_side = y_side * y_side;
    long long total = x_side + y_side;
    
    side = total;
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
int is_illegal_triangle(Point point1, Point point2, Point point3){

    //Overlapping points are illegal
    if(has_overlapping_points(point1, point2, point3)){
        return 1;
    }    
    /* rise/run */
    Slope slope_1_2 = calculate_slope(point1, point2);
    Slope slope_1_3 = calculate_slope(point1, point3);
    //Equal slopes means all 3 points form one straight line.
    int result = are_slopes_equal(slope_1_2, slope_1_3);
    return result;
}

void reduce_slope(Slope * slope){
    if(slope->rise == 0){
        slope->run = 1;
        return;
    }
    if(slope->run == 0){
        slope->rise = 1;
        return;
    }
    int divisor = gcd(slope->rise, slope->run);
    slope->rise = slope->rise/divisor;
    slope->run = slope->run/divisor;
}
    /**
     * \gcd(a,a) = a
     * \gcd(a,b) = \gcd(a - b,b)\quad, if a > b
     * \gcd(a,b) = \gcd(a, b-a)\quad,
     */
int gcd(long long a, long long b){
    if(a <= 1 || b <= 1){
        return 1;
    }
    if(a == b){
        return a;
    }
    if(a > b){
        return gcd(a-b, b);
    } else{
        return gcd(a, b-a);
    }
}

Slope calculate_slope(Point pointA, Point pointB){
    Slope slope;
    slope.rise = pointA.y - pointB.y;
    slope.run = pointA.x - pointB.x;
    insure_correct_slope(&slope);
    reduce_slope(&slope);
    return slope;
}

void insure_correct_slope(Slope* slope){
    if(slope->rise < 0 && slope->run < 0){
        slope->is_negative = 0;
        slope->rise = abs(slope->rise);
        slope->run = abs(slope->run);
    } else if( slope->rise >= 0 && slope->run >= 0){
        slope->is_negative = 0;
    } else {
        slope->is_negative = -1;
        slope->rise = abs(slope->rise);
        slope->run = abs(slope->run);
    }
}

int are_slopes_equal(Slope slopeA, Slope slopeB){
    return (slopeA.is_negative == slopeB.is_negative) && (slopeA.rise == slopeB.rise) && (slopeA.run == slopeB.run);
}

int are_points_equal(Point pointA, Point pointB){
    long long x = pointA.x == pointB.x;
    long long y = pointA.y == pointB.y;
    return y && x;
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

int dot_product(Point point_A, Point point_B, Point origin){
    
    long long x = (point_A.x-origin.x)*(point_B.x-origin.x);
    long long y = (point_A.y-origin.y)*(point_B.y-origin.y);
    
    long long result = x+y;
    
    if( result < 0){
        return -1;
    }
    if( result > 0){
        return 1;
    }
    
    return 0;
}


triangle_side_type find_triangle_side_type(long long sides[])
{
    triangle_side_type result;
    long long s1 = sides[0];
    long long s2 = sides[1];
    long long s3 = sides[2];
    
    
    if(s1 == s2){
        if(s2 == s3){
            result = eq;
        } else{
            result = is;
        }
    }else if(s2 == s3){
        result = is;
    } else{
        result = sc;
    }
    return result;
    
}
triangle_angle_type find_triangle_angle_type(long long angles[])
{
    if(angles[0] < 0){
        return ob;
    }
    
    if(angles[0] > 0){
        return ac;
    }
    
    return ri;
}

char* triangle_classification(long long sides[], long long angles[])
{
    triangle_side_type side_type = find_triangle_side_type(sides);
    triangle_angle_type angle_type = find_triangle_angle_type(angles);
    
    switch(side_type){
        
        case sc:
        {
         switch(angle_type){
             case ac:
             {
                 return SCALENE_ACUTE;
             }
             case ri:
             {
                 return SCALENE_RIGHT;
             }
             case ob:
             {
                 return SCALENE_OBTUSE;
             }
         }   
        }
        case is:
        {
            switch(angle_type){
             case ac:
             {
                 return ISOSCELES_ACUTE;
             }
             case ri:
             {
                 return ISOSCELES_RIGHT;
             }
             case ob:
             {
                 return ISOSCELES_OBTUSE;
             }
         } 
        }
        case eq:
        {
             return EQUILATERAL_ACUTE;
        }
    }
    
    
    
    
    
    
    
}