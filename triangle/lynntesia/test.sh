#!/bin/bash
# tests for triangle program

# not a triangle
./triangle 0 0 0 0 1 2

# not a triangle
./triangle 0 0 0 0 0 0

#right triangle
./triangle 3 3 3 7 9 3

#right triangle
./triangle -2 -3 2 1 5 -2

# obtuse
./triangle 0 0 -1 4 4 0

# scalene acute
./triangle 0 0 1 4 4 0

#isosceles
./triangle 0 0 0 4 4 4 4 0

# scalene
./triangle -5 2 -2 5 2 -5

# obtuse
./triangle -5 4 4 3 1 1




