#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Point {
  int x;
  int y;
} Point;

double distance(Point a, Point b) {
  int changeInX = abs(a.x - b.x);
  int changeInY = abs(a.y - b.y);
  return sqrt(changeInX * changeInX + changeInY * changeInY);
}

double angleLawOfCos(double a, double b, double c) {
  return acos((a * a + b * b - c * c) / (2 * a * b));
}

int main(int argc, char** argv) {
  if (argc != 7) {
    printf("Please follow the format\n$ %s <x1> <y1> <x2> <y2> <x3> <y3>\n",
      argv[0]);
    return 1;
  }

  Point points[3];
  points[0].x = atoi(argv[1]);
  points[0].y = atoi(argv[2]);
  points[1].x = atoi(argv[3]);
  points[1].y = atoi(argv[4]);
  points[2].x = atoi(argv[5]);
  points[2].y = atoi(argv[6]);

  double lengths[3];
  lengths[0] = distance(points[0], points[1]);
  lengths[1] = distance(points[1], points[2]);
  lengths[2] = distance(points[2], points[0]);

  if (lengths[0] == lengths[1] + lengths[2] ||
      lengths[1] == lengths[0] + lengths[2] ||
      lengths[2] == lengths[0] + lengths[1]) {
    printf("not a triangle\n");
    return 0;
  }

  char *sideName;
  if (lengths[0] == lengths[1] && lengths[0] == lengths[2]) {
    sideName = "equilateral";
  } else if (lengths[0] == lengths[1] || lengths[0] == lengths[2] ||
      lengths[1] == lengths[2]) {
    sideName = "isosceles";
  } else {
    sideName = "scalar";
  }

  double angles[3];
  angles[0] = angleLawOfCos(lengths[0], lengths[1], lengths[2]);
  angles[1] = angleLawOfCos(lengths[1], lengths[2], lengths[0]);
  angles[2] = angleLawOfCos(lengths[2], lengths[0], lengths[1]);

  char *angleName;
  if (angles[0] > asin(1) || angles[1] > asin(1) || angles[2] > asin(1)) {
    angleName = "obtuse";
  } else if (angles[0] == asin(1) || angles[1] == asin(1) ||
      angles[2] == asin(1)) {
    angleName = "right";
  } else {
    angleName = "acute";
  }

  printf("%s %s\n", sideName, angleName);

  return 0;
}