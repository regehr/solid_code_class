#include <stdio.h>
#include <stdlib.h>

#include "triangle.h"

int main(int argc, char **argv) {
  if (argc != 7) {
    printf("Usage: %s x1 y1 x2 y2 x3 y3\n", argv[0]);
    return 1;
  }

  Point a = {.x = atoi(argv[1]), .y = atoi(argv[2])};
  Point b = {.x = atoi(argv[3]), .y = atoi(argv[4])};
  Point c = {.x = atoi(argv[5]), .y = atoi(argv[6])};

  printf("%s\n", analyzeTriangle(a, b, c));
}
