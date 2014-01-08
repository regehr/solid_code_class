#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

/* convert radians to degrees */
#define DEG(x) ((x) * (180 / M_PI))
/* convert degrees to radians */
#define RAD(x) ((x) * (M_PI / 180))
#define ABSOLUTE_ERROR 0.0000001

#define NOT_TRI "not a triangle"

#define ISOC "isosceles"
#define EQUI "equilateral"
#define SCAL "scalene"

#define RIGHT "right"
#define ACUTE "acute"
#define OBTUSE "obtuse"

struct point {
    double x;
    double y;
};

bool double_equal(double a, double b) {
    if (a > b) {
        return (a - b) < ABSOLUTE_ERROR;
    } else {
        return (b - a) < ABSOLUTE_ERROR;
    }
}

/* Calculate the distance between two points in the cartesian plane */
double distance_between(struct point point_a, struct point point_b) {
    return sqrt( powl(point_b.x - point_a.x, 2) + 
                 powl(point_b.y - point_a.y, 2) );
}


/* calculate an angle in the triangle using hte cosine rule 
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

    if (! double_equal(out_angle[0] + 
                       out_angle[1] + 
                       out_angle[2], RAD(180.0))) {
        return -1;
    }

    return 0;
}

int figure_triangle(struct point points[3], 
                    char ** out_type, 
                    char ** out_angle) {
    double angle[3];
    if (calculate_angles(points, angle) < 0) { return -1; }

    /* if it is not obtuse of right then it must be acute */
    *out_angle = ACUTE;
    for (int i = 0; i < 3; i++) {
        if (double_equal(angle[i], 0.0)) { return -1; }
        else if (double_equal(angle[i], RAD(90.0))) { *out_angle = RIGHT; }
        else if (DEG(angle[i]) > 90.0) { *out_angle = OBTUSE; } 
    }

    /* if it not equilateral or isosceles then it must be scalene */
    *out_type = SCAL;
    if (double_equal(angle[0], angle[1]) 
            && double_equal(angle[1], angle[2])
            && double_equal(angle[0], angle[2])) {
        *out_type = EQUI;
        return 0;
    }
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) { continue; }
            if (double_equal(angle[i], angle[j])) { 
                *out_type = ISOC; 
                return 0;
            }
        }
    }

    return 0;
}

int main(int argc, char * argv[]) {
    if (argc < 7) {
        fputs("usage: ./tri x1 y1 x2 y2 x3 y3\n", stderr);
        return 1;
    }
    struct point points[3];

    /* parse the points */
    points[0].x = atof(argv[1]);
    points[0].y = atof(argv[2]);

    points[1].x = atof(argv[3]);
    points[1].y = atof(argv[4]);

    points[2].x = atof(argv[5]);
    points[2].y = atof(argv[6]);

    char * type = "";
    char * angle = "";
    if (figure_triangle(points, &type, &angle) >= 0) {
        printf("%s %s\n", type, angle);
    } else {
        printf("not a triangle\n");
    }

    return 0;
}
