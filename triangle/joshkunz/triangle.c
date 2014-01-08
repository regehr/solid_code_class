#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define ABSOLUTE_ERROR 0.00000000001

/* convert radians to degrees */
#define DEG(x) ((x) * (180 / M_PI))
/* convert degrees to radians */
#define RAD(x) ((x) * (M_PI / 180))

struct point {
    double x;
    double y;
};

/* check equality of two doubles */
bool double_equal(double a, double b) {
    if (a > b) {
        return (a - b) < ABSOLUTE_ERROR;
    } else {
        return (b - a) < ABSOLUTE_ERROR;
    }
}

/* Calculate the distance between two points in the Cartesian plane */
double distance_between(struct point point_a, struct point point_b) {
    return sqrt( pow(point_b.x - point_a.x, 2) + 
                 pow(point_b.y - point_a.y, 2) );
}

/* calculate an angle in the triangle using the cosine rule and
 * the edge-lengths of the triangle. */
double angle_given(double first_adj, double second_adj, double opposite) {
    return acos( (pow(first_adj, 2) + 
                  pow(second_adj, 2) - 
                  pow(opposite, 2)) / 
                 (2 * first_adj * second_adj));
}

int calculate_angles(struct point points[3], double out_angle[3]) {
    double edge[3];
    edge[0] = distance_between(points[0], points[1]);
    edge[1] = distance_between(points[1], points[2]);
    edge[2] = distance_between(points[2], points[0]);

    out_angle[0] = angle_given(edge[0], edge[2], edge[1]);
    out_angle[1] = angle_given(edge[1], edge[0], edge[2]);
    out_angle[2] = angle_given(edge[2], edge[1], edge[0]);

    return 0;
}

const char * triangle_angle(double angle[3]) {
    /* if not obtuse or right, than it must be acute */
    char * name = "acute";
    for (int i = 0; i < 3; i++) {
        //printf("Angle [%d]: %.12f\n", i, angle[i]);
        
        /* if the same point is given for every input, the angles will be
         * NaN, and if any angle is 0 than two points are colinear. */
        if (isnan(angle[i]) || double_equal(angle[i], 0.0)) { 
            return NULL; 
        } else if (double_equal(angle[i], RAD(90.0))) { 
            name = "right"; 
        } else if (DEG(angle[i]) > 90.0) { 
            name = "obtuse";
        } 
    }
    return name;
}

const char * triangle_type(double angle[3]) {
    /* if it not equilateral or isosceles then it must be scalene */
    char * name = "scalene";
    if (double_equal(angle[0], angle[1]) 
            && double_equal(angle[1], angle[2])
            && double_equal(angle[0], angle[2])) {
        name = "equilateral";
    } else if (double_equal(angle[0], angle[1]) 
            || double_equal(angle[1], angle[2]) 
            || double_equal(angle[0], angle[2])) {
        name = "isosceles";
    }

    return name;
}

int main(int argc, char * argv[]) {
    if (argc < 7) {
        fputs("usage: ./tri x1 y1 x2 y2 x3 y3\n", stderr);
        return 1;
    }
    struct point points[3];
    double angles[3];

    /* parse the points */
    points[0].x = atof(argv[1]);
    points[0].y = atof(argv[2]);

    points[1].x = atof(argv[3]);
    points[1].y = atof(argv[4]);

    points[2].x = atof(argv[5]);
    points[2].y = atof(argv[6]);

    calculate_angles(points, angles);

    const char * type = triangle_type(angles);
    const char * angle = triangle_angle(angles);

    if (type == NULL || angle == NULL) {
        printf("not a triangle\n");
    } else {
        printf("%s %s\n", type, angle);
    }

    return 0;
}
