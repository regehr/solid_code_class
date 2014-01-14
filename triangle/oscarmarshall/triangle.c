#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  long long x;
  long long y;
} Point;

long long square(long long number) {
  assert(number < 0x7fffffff);
  return number * number;
}

long long distanceSquared(Point a, Point b) {
  return square(abs(a.x - b.x)) + square(abs(a.y - b.y));
}

int angleTypeFromLengthsSquared(long long a, long long b, long long c) {
  return c - a - b;
}

char *analyzeTriangle(Point a, Point b, Point c) {
  Point bTransformed = {.x = b.x - a.x, .y = b.y - a.y};
  Point cTransformed = {.x = c.x - a.x, .y = c.y - a.y};

  if (bTransformed.x * cTransformed.y == bTransformed.y * cTransformed.x) {
    return "not a triangle";
  }

  long long lengthsSquared[3];
  lengthsSquared[0] = distanceSquared(a, b);
  lengthsSquared[1] = distanceSquared(b, c);
  lengthsSquared[2] = distanceSquared(c, a);

  char *sideName;
  if (lengthsSquared[0] == lengthsSquared[1] ||
      lengthsSquared[0] == lengthsSquared[2] ||
      lengthsSquared[1] == lengthsSquared[2]) {
    sideName = "isosceles";
  } else {
    sideName = "scalene";
  }

  int typeOfLargestAngle;
  if (lengthsSquared[0] >= lengthsSquared[1] &&
      lengthsSquared[0] >= lengthsSquared[2]) {
    typeOfLargestAngle = angleTypeFromLengthsSquared(lengthsSquared[1],
      lengthsSquared[2], lengthsSquared[0]);
  } else if (lengthsSquared[1] >= lengthsSquared[0] &&
      lengthsSquared[1] >= lengthsSquared[2]) {
    typeOfLargestAngle = angleTypeFromLengthsSquared(lengthsSquared[0],
      lengthsSquared[2], lengthsSquared[1]);
  } else {
    typeOfLargestAngle = angleTypeFromLengthsSquared(lengthsSquared[0],
      lengthsSquared[1], lengthsSquared[2]);
  }

  char *angleName;
  if (typeOfLargestAngle == 0) angleName = "right";
  else if (typeOfLargestAngle > 0) angleName = "obtuse";
  else angleName = "acute";

  char *result = malloc(20 * sizeof(char));
  strcpy(result, sideName);
  strcat(result, " ");
  strcat(result, angleName);

  return result;
}

int main(int argc, char **argv) {
  Point a, b, c;
  if (argc != 7 ||
      !sscanf(argv[1], "%lld", &a.x) ||
      !sscanf(argv[2], "%lld", &a.y) ||
      !sscanf(argv[3], "%lld", &b.x) ||
      !sscanf(argv[4], "%lld", &b.y) ||
      !sscanf(argv[5], "%lld", &c.x) ||
      !sscanf(argv[6], "%lld", &c.y)) {
    printf("Usage: %s x1 y1 x2 y2 x3 y3\n", argv[0]);
    return 1;
  }

  printf("%s\n", analyzeTriangle(a, b, c));

  return 0;
}
