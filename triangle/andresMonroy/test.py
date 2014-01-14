import subprocess
import sys
import shlex

file = open("test.txt", "r")

passed = 0;
failed = 0;

for line in file:
    points = line.split()
    expected = next(file)
    out = subprocess.check_output(["./triangle", points[0], points[1], points[2], points[3], points[4], points[5]])
    output = out.decode("utf-8")
    if (output != expected):
        print("FAIL\tActual: {0}\n\tExpected: {1}".format(output.rstrip(), expected))
        failed += 1
    else:
        passed += 1

file.close
print("{0} tests passed\n{1} test failed".format(passed, failed))
