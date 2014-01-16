#borrowed from user andresMonroy
import subprocess
import sys
import shlex
import random

tests_passed = 0
tests_failed = 0

file = open("test.txt", "r")

for line in file:
	points = line.split()
	expected = next(file)
	out = subprocess.check_output(["./triangle", points[0], points[1], points[2], points[3], points[4], points[5]])
	output = out.decode("utf-8")

	if(output != expected):
		print("Test Failed\nInput: {0}\nExpected: {1}\nAcutal: {2}".format(line.rstrip(), expected.rstrip(), output))
		tests_failed += 1
	else:
		tests_passed += 1

file.close
print("{0} tests passed\n{1} tests failed".format(tests_passed, tests_failed))