#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define UNUSED(x) __attribute__((unused)) x
#define POS_SHIFT ((sizeof(long long) << 3) - 2)

#define POW2(x) ((x) * (x))

struct point {
    long long x;
    long long y;
};

/* Calculate the distance between two points on a Cartesian plane */
long long distance(struct point point_a, struct point point_b) {
    return POW2(point_b.x - point_a.x) + POW2(point_b.y - point_a.y);
}

/* Check if three points lie on the same line */
bool are_collinear(struct point point_a, struct point point_b, struct point point_c) {
    return ( (point_a.x * (point_b.y - point_c.y)) +
             (point_b.x * (point_c.y - point_a.y)) +
             (point_c.x * (point_a.y - point_b.y)) ) == 0;
}

/* Perform an addition with well-defined overflow detection. Returns true if
 * the addition overflowed. If an overflow occurs the value of 'out' is 
 * undefined. */
bool safe_add(long long *out, long long a, long long b) {
    long long lower_add = (~(1LL << POS_SHIFT) & a) + (~(1LL << POS_SHIFT) & b);
    if ((lower_add >> POS_SHIFT) & ((a >> POS_SHIFT) | (b >> POS_SHIFT))) {
        return true;
    } else if ((a >> POS_SHIFT) & (b >> POS_SHIFT)) {
        return true;
    } else {
        *out = a + b; 
        return false;
    }
}

/* Figure out the indexes of the largest edge and smaller edges */
void assign_edges(long long edges[3], int *oa, int *ob, int *oc) {
    int a, b, c = 0;
    if (edges[1] > edges[c]) { a = c; c = 1; } else { a = 1; }
    if (edges[2] > edges[c]) { b = c; c = 2; } else { b = 2; }
    *oa = a; *ob = b; *oc = c;
}

const char * triangle_angle(long long edge[3]) {
    int ai, bi, ci;
    long long ab;
    assign_edges(edge, &ai, &bi, &ci);
    /* if addition overflows then we know for sure that a + b is
     * larger than c */
    if (safe_add(&ab, edge[ai], edge[bi])) {
        return "acute";
    } 

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
     * Cartesian grid, so the equilateral case is not handled.  */
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

    if (are_collinear(points[0], points[1], points[2])) {
        printf("not a triangle\n");
    } else {
        const char * type = triangle_type(edges);
        const char * angle = triangle_angle(edges);

        printf("%s %s\n", type, angle);
    }

    return 0;
}
