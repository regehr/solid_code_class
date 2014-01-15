import sys
import subprocess
import math
import random
from itertools import combinations, chain, permutations

ABSOLUTE_ERROR = 0.00000000001
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
    return [rand_point() for x in xrange(3)]

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
                for x in xrange(3)]
    angles = [angle(edges[x], edges[(2 + x) % 3], edges[(1 + x) % 3])
                for x in xrange(3)]

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

def test_output(binary, triangle, expected):
    "Test the output of the binary given the triangle"
    args = [binary] + map(str, chain.from_iterable(triangle))
    process = subprocess.Popen(args, stdout=subprocess.PIPE)
    # Get the binary data from 
    got = process.communicate()[0]
    return (got, got == expected)

def read_triangle(line):
    "Read a triangle from a test-input file"
    numbers = line.strip().split(" ")
    numbers = map(int, numbers)
    return [(numbers[0], numbers[1]),
            (numbers[2], numbers[3]),
            (numbers[4], numbers[5])]


def print_error(triangle, expected, got):
    "Print out an error message if a triangle is mis-classified"
    print "~~~ Failed test. ~~~"
    pprint(triangle)
    print "[Expected]", repr(expected)
    print "[Got]     ", repr(got)

def iter_test(testgen, binary, display_error=True, fail_fast=False):
    failed = 0
    total = 0
    for (triangle, expected) in testgen:
        got, match = test_output(binary, triangle, expected)
        if not match:
            failed += 1
            if display_error: print_error(triangle, expected, got)
        total += 1
        if fail_fast and failed > 0: break
    return failed, total 

def permute_glue(generator):
    for (triangle, expected) in generator:
        for order in permutations(triangle, 3):
            yield (order, expected)

def fuzz(test_count):
    "Run test_count property formatted tests"
    for test in xrange(test_count):
        triangle = rand_triangle()
        yield (triangle, classify_triangle(triangle))

def test_file(file):
    "check inputs from a test file"
    for line in file:
        triangle = read_triangle(line) 
        expected = file.next()
        yield (triangle, expected)

if __name__ == "__main__":
    from pprint import pprint
    from argparse import ArgumentParser

    parser = ArgumentParser()
    parser.add_argument("--fuzz", "-u")
    parser.add_argument("--permute", "-p", action="store_true")
    parser.add_argument("--file", "-f")
    parser.add_argument("--quiet", "-q", action="store_false")
    parser.add_argument("--fail-fast", "-ff", action="store_true")
    parser.add_argument("--input", "-i", action="store_true")
    parser.add_argument("binary", nargs="+")
    args = parser.parse_args()

    if args.input:
        print classify_triangle(read_triangle(args.binary[0])),

    for binary in args.binary:
        print "Testing:", binary
        gen = None
        f = None
        if args.fuzz:
            gen = fuzz(int(args.fuzz))
        else:
            f = open(args.file)
            gen = test_file(f)
        if args.permute:
            gen = permute_glue(gen)
        failed, total = iter_test(gen, binary, 
                                  display_error=args.quiet, 
                                  fail_fast=args.fail_fast) 
        print "{0} tests passed, {1} tests failed.".format(total - failed, failed)
        if f is not None: f.close()
