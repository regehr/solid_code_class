#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

struct Point {
    unsigned long long x;
    unsigned long long y;
};

bool is_invalid_triangle(struct Point points[3]){
    struct Point d_AB = { .x = points[0].x - points[1].x, .y = points[0].y - points[1].y };
    struct Point d_AC = { .x = points[0].x - points[2].x, .y = points[0].y - points[2].y };
    return (d_AB.x * d_AC.y) == (d_AB.y * d_AC.x);
}

unsigned long long find_distance(struct Point p1, struct Point p2){
    unsigned long long dx = p2.x - p1.x;
    unsigned long long dy = p2.y - p1.y;
    return (dx*dx) + (dy*dy);
}

char* get_triangle_type(unsigned long long sides[3]){
    if (sides[0] == sides[1] || sides[1] == sides[2] || sides[2] == sides[0])
        return "isosceles";
    return "scalene";
}

int comp(const void* aa, const void* bb){
    const unsigned long long *a = aa, *b = bb;
    return (*a < *b) ? -1 : (*a > *b);
}

char* get_angle_type(unsigned long long sides[3]){
    qsort(sides, 3, sizeof(unsigned long long), comp);
    unsigned long long angle_type = sides[2] - sides[1] - sides[0];
    if (sides[2] > (sides[1] + sides[0])){
        return "obtuse";
    } else if (sides[2] < (sides[1] + sides[0])){
        return "acute";
    }
    return "right";
}

/**
 * Find the type of triangle from the triplet of points given.
 * out: type - isosceles || scalene
 * out: angle - acute || obtuse || right
 */
void find_triangle(struct Point points[3], char** type, char** angle){
    /* NOTE: cannot form an equilateral triangle with integer inputs */
    unsigned long long sides[3];
    
    /* finds sides and angles */
    sides[0] = find_distance(points[0], points[1]);
    sides[1] = find_distance(points[0], points[2]);
    sides[2] = find_distance(points[1], points[2]);
    *type = get_triangle_type(sides);
    *angle = get_angle_type(sides);
}

int main (int argc, char* argv[]){
    assert(argc == 7);
    char* type = "";
    char* angle = "";
    struct Point points[3];
    
    sscanf(argv[1], "%lld", &points[0].x);
    sscanf(argv[2], "%lld", &points[0].y);
    sscanf(argv[3], "%lld", &points[1].x);
    sscanf(argv[4], "%lld", &points[1].y);
    sscanf(argv[5], "%lld", &points[2].x);
    sscanf(argv[6], "%lld", &points[2].y);
    
    /* Same slope = not a triangle */
    if (is_invalid_triangle(points)){
        printf("not a triangle\n");
        return 0;
    }
    find_triangle(points, &type, &angle);
    printf("%s %s\n", type, angle);
    return 0;
}
