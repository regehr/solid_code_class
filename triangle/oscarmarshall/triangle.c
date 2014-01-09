#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "triangle.h"

#define PI acos(-1)
#define EPSILON PI / pow(2, 16)

int equal(double a, double b) {
  return fabs(a - b) < EPSILON;
}

double distance(Point a, Point b) {
  return sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
}

double angleLawOfCos(double a, double b, double c) {
  return acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b));
}

char *analyzeTriangle(Point a, Point b, Point c) {
  double lengths[3];
  lengths[0] = distance(a, b);
  lengths[1] = distance(b, c);
  lengths[2] = distance(c, a);

  if (lengths[0] == lengths[1] + lengths[2] ||
      lengths[1] == lengths[0] + lengths[2] ||
      lengths[2] == lengths[0] + lengths[1]) {
    return "not a triangle";
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
  if (equal(angles[0], PI / 2) || equal(angles[1], PI / 2) ||
      equal(angles[2], PI / 2)) {
    angleName = "right";
  } else if (angles[0] > asin(1) || angles[1] > asin(1) ||
      angles[2] > asin(1)) {
    angleName = "obtuse";
  } else {
    angleName = "acute";
  }

  char *result = malloc(20 * sizeof(char));
  strcpy(result, sideName);
  strcat(result, " ");
  strcat(result, angleName);

  return result;
}
