#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Point {
    double x;
    double y;
};

double find_slope(double x1, double x2, double y1, double y2){
    double dy = y2 - y1;
    double dx = x2 - x1;
    return dy/dx;
}

double find_distance(struct Point p1, struct Point p2){
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx*dx + dy*dy);
}

double to_degrees(double rads){
    return rads*(180.0/M_PI);
}

double find_angle(double a, double b, double c) {
    return to_degrees(acos((b*b + c*c - a*a) / (2*b*c)));
}

bool is_equilateral(double sides[3]){
    return sides[0] == sides[1] && sides[1] == sides[2] && sides[2] == sides[0];
}

double get_largest_angle(double angles[3]){
    if (angles[0] > angles[1] && angles[0] > angles[2]){
        return angles[0];
    } else if (angles[1] > angles[0] && angles[1] > angles[2]){
        return angles[1];
    } else if (angles[2] > angles[0] && angles[2] > angles[1]){
        return angles[2];
    } else {
		return angles[0];
    }
}

bool is_right(double angles[3]){
    /* slopes of perpendicular lines are negative reciprocals */
    double angle = get_largest_angle(angles);
    return angle >= 90 && (angle - 90) < .00000000001;
}

bool is_isosceles(double sides[3]){
    return sides[0] == sides[1] || sides[1] == sides[2] || sides[2] == sides[0];
}

bool is_obtuse(double angles[3]){
    return angles[0] > 90 || angles[1] > 90 || angles[2] > 90;
}

void find_triangle(struct Point points[3], char** type, char** angle){
    char* EQI = "equilateral";
    char* ISO = "isosceles";
    char* RIGHT = "right";
    char* SCA = "scalene";
    char* OBT = "obtuse";
    char* ACU = "acute";
    double sides[3];
    double angles[3];
    
    /* finds sides and angles */
    sides[0] = find_distance(points[0], points[1]);
    sides[1] = find_distance(points[0], points[2]);
    sides[2] = find_distance(points[1], points[2]);
    angles[0] = find_angle(sides[1], sides[2], sides[0]);
    angles[1] = find_angle(sides[0], sides[1], sides[2]);
    angles[2] = find_angle(sides[2], sides[1], sides[0]);
    
    /* check equilateral */
    if (is_equilateral(sides)){
        *type = EQI;
        *angle = ACU;
        return;
    }
    
    /* check isosceles variants */
    if (is_isosceles(sides)){
        *type = ISO;
    } else {
        *type = SCA;
    }
    
    /* check angle type */
    if (is_right(angles)){
        *angle = RIGHT;
        return;
    }
    if (is_obtuse(angles)){
        *angle = OBT;
    } else {
        *angle = ACU;
    }
}

int main (int argc, char* argv[]){
    char* type = "";
    char* angle = "";
    struct Point points[3];
    points[0].x = atof(argv[1]);
    points[0].y = atof(argv[2]);
    points[1].x = atof(argv[3]);
    points[1].y = atof(argv[4]);
    points[2].x = atof(argv[5]);
    points[2].y = atof(argv[6]);
    
    double slope_AB = find_slope(points[0].x, points[1].x, points[0].y, points[1].y);
    double slope_AC = find_slope(points[0].x, points[2].x, points[0].y, points[2].y);
    
    /* Same slope = not a triangle */
    if (slope_AB == slope_AC){
        printf("not a triangle\n");
        return 0;
    }
    
    find_triangle(points, &type, &angle);
    printf("%s %s\n", type, angle);
    return 0;
}
