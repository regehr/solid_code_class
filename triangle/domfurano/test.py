#! /usr/bin/python

import subprocess

file = open("test.txt", "r")

correct = 0;
total = 0;

for line in file:
    coords = line.split()
    expected = file.next()
    output = subprocess.check_output(["./triangle", coords[0], coords[1], coords[2], coords[3], coords[4], coords[5]])
    if (output != expected):
        print "Test failed!\nInput: \t\t{0}\nExpected: \t{1}\nOutput: \t{2}".format(coords, expected.rstrip(), output)
    else:
        correct+=1
    total+=1

file.close()

print "{0} out of {1} tests passed.".format(correct, total)

