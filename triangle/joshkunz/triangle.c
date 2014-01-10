#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define UNUSED(x) __attribute__((unused)) x
#define POW2(x) ((x) * (x))

struct point {
    long long x;
    long long y;
};

/* Calculate the distance between two points in the Cartesian plane */
long long distance(struct point point_a, struct point point_b) {
    return POW2(point_b.x - point_a.x) + POW2(point_b.y - point_a.y);
}

bool is_collinear(struct point point_a, struct point point_b, struct point point_c) {
    return ( (point_a.x * (point_b.y - point_c.y)) +
             (point_b.x * (point_c.y - point_a.y)) +
             (point_c.x * (point_a.y - point_b.y)) ) == 0;
}

/* Figure out the index of the largest edge */
void max_index(long long edges[3], int *a, int *b, int *c) {
    *c = 0;
    if (edges[1] > edges[*c]) { *a = *c; *c = 1; }
    else { *a = 1; }
    if (edges[2] > edges[*c]) { *b = *c; *c = 2; }
    else { *b = 2; }
}

const char * triangle_angle(long long edge[3]) {
    int ai, bi, ci;
    max_index(edge, &ai, &bi, &ci);
    long long ab = edge[ai] + edge[bi];

    char * name = "acute";
    if (ab == edge[ci]) {
        name = "right";
    } else if (ab < edge[ci]) {
        name = "obtuse";
    }

    return name; 
} 

const char * triangle_type(long long edge[3]) {
    /* We cannot have an equilateral triangle with only integer inputs on a
     * cartesian grid. */
    char * name = "scalene";
    if (edge[0] == edge[1] 
            || edge[1] == edge[2]
            || edge[0] ==  edge[2]) {
        name = "isosceles";
    }

    return name;
}

int main(UNUSED(int argc), char * argv[]) {
    struct point points[3];
    long long edges[3];

    /* parse the points */
    points[0].x = atoi(argv[1]);
    points[0].y = atoi(argv[2]);

    points[1].x = atoi(argv[3]);
    points[1].y = atoi(argv[4]);

    points[2].x = atoi(argv[5]);
    points[2].y = atoi(argv[6]);

    edges[0] = distance(points[0], points[1]);
    edges[1] = distance(points[1], points[2]);
    edges[2] = distance(points[2], points[0]);

    if (is_collinear(points[0], points[1], points[2])) {
        printf("not a triangle\n");
    } else {
        const char * type = triangle_type(edges);
        const char * angle = triangle_angle(edges);

        printf("%s %s\n", type, angle);
    }

    return 0;
}
