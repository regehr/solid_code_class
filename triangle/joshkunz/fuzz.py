import subprocess
import math
import random
from itertools import combinations, chain

import sys
from pprint import pprint

BIN = "./triangle"
ABSOLUTE_ERROR = 0.000001
POINT_MAX = (2 ** 31) - 1

def _eq((x, y)):
    return (max(x, y) - min(x, y)) < ABSOLUTE_ERROR

def eq(*floats):
    return all(map(_eq, combinations(floats, 2)))

def deg(x): return x * (180.0 / math.pi)
def rad(x): return x * (math.pi / 180.0)

def cdist((x1, y1), (x2, y2)):
    return math.sqrt( ((x2 - x1) ** 2) + ((y2 - y1) ** 2))

def angle(first_adj, second_adj, opposite):
    return math.acos( ((first_adj ** 2) + 
                       (second_adj ** 2) -
                       (opposite ** 2)) /
                      (2 * first_adj * second_adj) )

def rand_point():
    return (random.randrange(POINT_MAX),
            random.randrange(POINT_MAX))

def rand_triangle():
    return [rand_point() for x in range(3)]

def what_triangle(points):
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

if __name__ == "__main__":
    for test in range(int(sys.argv[1])):
        triangle = rand_triangle()
        expected = what_triangle(triangle)
        got = subprocess.check_output([BIN] + 
                                      map(str, chain.from_iterable(triangle)))
        if got != expected: 
            print "~~~ Failed test. ~~~"
            pprint(triangle)
            print "[Expected]", expected
            print "[Got]     ", got
            sys.exit(1)
