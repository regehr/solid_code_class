import sys
import subprocess
import math
import random
from itertools import combinations, chain

BIN = "./triangle"
ABSOLUTE_ERROR = 0.000001
POINT_MAX = (2 ** 31) - 1

def deg(x): return x * (180.0 / math.pi)
def rad(x): return x * (math.pi / 180.0)

def eq(*floats):
    def _eq((x, y)):
        return (max(x, y) - min(x, y)) < ABSOLUTE_ERROR
    return all(map(_eq, combinations(floats, 2)))

def rand_point():
    return (random.randrange(POINT_MAX),
            random.randrange(POINT_MAX))

def rand_triangle():
    return [rand_point() for x in range(3)]

def cdist((x1, y1), (x2, y2)):
    "get the length between two coordinates"
    return math.sqrt( ((x2 - x1) ** 2) + ((y2 - y1) ** 2))

def angle(first_adj, second_adj, opposite):
    "Get angle of a triangle"
    return math.acos( ((first_adj ** 2) + 
                       (second_adj ** 2) -
                       (opposite ** 2)) /
                      (2 * first_adj * second_adj) )

def classify_triangle(points):
    "triangle classification in python"
    edges = [cdist(points[x], points[(x + 1) % 3]) 
                for x in range(3)]
    angles = [angle(edges[x], edges[(2 + x) % 3], edges[(1 + x) % 3])
                for x in range(3)]
    assert eq(sum(angles), rad(180.0))

    if 0.0 in angles: return "not a triangle"
    a = "acute"
    if any(map(lambda x: eq(x, rad(90.0)), angles)):
        a = "right"
    elif any(map(lambda x: x > rad(90.0), angles)):
        a = "obtuse"

    t = "scalene"
    if angles[0] == angles[1] == angles[2]:
        t = "equal"
    elif any(map(lambda (a, b): a == b, combinations(angles, 2))):
        t = "isosceles"
    return "{0} {1}\n".format(t, a)

def test_output(triangle, expected, bin=BIN):
    "Test the output of the binary given the triangle"
    args = [bin] + map(str, chain.from_iterable(triangle))
    got = subprocess.check_output(args)
    return (got, got == expected)

def print_error(triangle, expected, got):
    "Print out an error message if a triangle is mis-classified"
    print "~~~ Failed test. ~~~"
    pprint(triangle)
    print "[Expected]", expected
    print "[Got]     ", got
    sys.exit(1)

def fuzz(test_count):
    "Run test_count property formatted tests"
    for test in range(test_count):
        triangle = rand_triangle()
        expected = classify_triangle(triangle)
        got, match = test_output(triangle, expected)
        if not match: print_error(triangle, expected, got)

def read_triangle(line):
    "Read a triangle from a test-input file"
    numbers = line.strip().split(" ")
    numbers = map(int, numbers)
    return [(numbers[0], numbers[1]),
            (numbers[2], numbers[3]),
            (numbers[4], numbers[5])]

def test_file(file):
    "check inputs from a test file"
    triangle = []
    for line in file:
        triangle = read_triangle(line) 
        expected = file.next()
        got, match = test_output(triangle, expected)
        if not match: print_error(triangle, expected, got)

if __name__ == "__main__":
    from pprint import pprint
    from argparse import ArgumentParser

    parser = ArgumentParser()
    parser.add_argument("--fuzz", "-f")
    parser.add_argument("--test", "-t")
    args = parser.parse_args()

    if args.fuzz:
        fuzz(int(args.fuzz))
    else:
        with open(args.test) as f: test_file(f)
