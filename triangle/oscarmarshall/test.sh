#!/bin/bash

# usage: unit_test actual expected
unit_test() {
  : testNumber:=0
  ((testNumber++))
  printf 'Test %2i: ' "${testNumber}"
  if [[ "$1" = "$2" ]]; then
    printf 'PASSED\n'
  else
    printf 'FAILED\n'
    printf "  Actual:   $1\n"
    printf "  Expected: $2\n"
  fi
}
# isosceles obtuse
expected='isosceles obtuse'
unit_test "$(./triangle 0 1 2 0 4 1)" "${expected}"

# isosceles right
expected='isosceles right'
unit_test "$(./triangle 0 0 0 1 1 0)" "${expected}"

# isosceles acute
expected='isosceles acute'
unit_test "$(./triangle 0 2 1 0 2 2)" "${expected}"

# scalene obtuse
expected='scalene obtuse'
unit_test "$(./triangle 0 1 1 0 2 0)" "${expected}"

# scalene right
expected='scalene right'
unit_test "$(./triangle 0 0 0 2 1 0)" "${expected}"

# scalene acute
expected='scalene acute'
unit_test "$(./triangle 0 0 4 1 1 3)" "${expected}"

# not a triangle
expected='not a triangle'
unit_test "$(./triangle 0 0 0 0 0 0)" "${expected}"

# Usage: ./triangle x1 y1 x2 y2 x3 y3
expected='Usage: ./triangle x1 y1 x2 y2 x3 y3'
unit_test "$(./triangle)" "${expected}"
