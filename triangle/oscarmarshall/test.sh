#!/bin/bash

# usage: unit_test actual expected
unit_test() {
  ((test_number++))
  if [[ "$quiet" -eq 0 ]]; then
    printf 'Test %2i: ' "${test_number}"
  fi
  if [[ "$1" = "$2" ]]; then
    if [[ "$quiet" -eq 0 ]]; then
      printf 'PASSED\n'
    fi
  else
    if [[ "$quiet" -eq 1 ]]; then
      ((failed = 1))
    else
      printf 'FAILED\n'
      printf '  Actual:   %s\n' "$1"
      printf '  Expected: %s\n' "$2"
    fi
  fi
}

main() {
  if [[ "$1" = '-q' ]]; then
    ((quiet = 1))
  fi

  # isosceles obtuse
  expected='isosceles obtuse'
  unit_test "$(./triangle 0 1 2 0 4 1)" "${expected}"
  unit_test "$(./triangle 0 0 1073741822 1073741824 2147483646 2147483646)" \
            "${expected}"

  # isosceles right
  expected='isosceles right'
  unit_test "$(./triangle 0 0 0 1 1 0)" "${expected}"
  unit_test "$(./triangle 1 0 0 2147483646 2147483647 1)" "${expected}"

  # isosceles acute
  expected='isosceles acute'
  unit_test "$(./triangle 0 2 1 0 2 2)" "${expected}"

  # scalene obtuse
  expected='scalene obtuse'
  unit_test "$(./triangle 0 1 1 0 2 0)" "${expected}"
  unit_test "$(./triangle 0 0 1073741822 1073741824 2147483645 2147483647)" \
            "${expected}"

  # scalene right
  expected='scalene right'
  unit_test "$(./triangle 0 0 0 2 1 0)" "${expected}"

  # scalene acute
  expected='scalene acute'
  unit_test "$(./triangle 0 0 4 1 1 3)" "${expected}"
  unit_test "$(./triangle 1 0 0 2147483647 2147483647 1)" "${expected}"

  # not a triangle
  expected='not a triangle'
  unit_test "$(./triangle 0 0 0 0 0 0)" "${expected}"
  unit_test "$(./triangle 0 0 1073741823 1073741823 2147483646 2147483646)" \
            "${expected}"

  # Usage: ./triangle x1 y1 x2 y2 x3 y3
  #expected='Usage: ./triangle x1 y1 x2 y2 x3 y3'
  #unit_test "$(./triangle)" "${expected}"

  if [[ "$quiet" -eq 1 ]]; then
    if [[ "$failed" -eq 1 ]]; then
      printf "FAILED\n"
    else
      printf "PASSED\n"
    fi
  fi
}

((quiet = 0))
((test_number = 0))
((failed = 0))

main "$@"
