import subprocess
from random import randrange

print "Beginning tests. This might take a minute."

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

def rotate_90(tri):
    return [tri[0], tri[1], str(-(int(tri[3]) - int(tri[1]))), tri[2], str(-(int(tri[5]) - int(tri[1]))), tri[4]]

check_triangle(tri, name):
    

for i in range(0, 100):
    x = randrange(2147483647)
    y = randrange(2147483647)
    mod = 1
    while (x + mod*2 <= 2147483647 and y + mod*2 <= 2147483647 and x - mod*2 >= 0):
        triangle = [str(x), str(y), str(x - mod), str(y + mod), str(x + mod), str(y + mod)]
        check_triangle(triangle, "isosceles right\n")

        assert (subprocess.check_output(["./triangle", str(x), str(y), str(x - mod), str(y + mod), str(x + mod), str(y + mod)]) == "isosceles right\n")
        assert (subprocess.check_output(["./triangle", str(x), str(y), str(x - mod*2), str(y + mod), str(x + mod), str(y + mod)]) == "scalene obtuse\n")
        assert (subprocess.check_output(["./triangle", str(x), str(y), str(x - mod*2), str(y + mod*2), str(x + mod), str(y + mod)]) == "scalene right\n")
        assert (subprocess.check_output(["./triangle", str(x), str(y), str(x - mod), str(y + mod*2), str(x + mod), str(y + mod)]) == "isosceles acute\n")
        assert (subprocess.check_output(["./triangle", str(x), str(y), str(x - mod*2), str(y + mod), str(x + mod*2), str(y + mod)]) == "isosceles obtuse\n")
        assert (subprocess.check_output(["./triangle", str(x), str(y), str(x - mod*2), str(y + mod*2), str(x + mod), str(y + mod*2)]) == "scalene acute\n")
        mod += 10000000
        correct += 6
        total += 6    

print "{0} out of {1} tests passed.".format(correct, total)

