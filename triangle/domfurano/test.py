import subprocess

print "Beginning test.\n"

file = open("test.txt", "r")

for line in file:
    coords = line.split()
    expected = file.next()
    output = subprocess.check_output(["./triangle", coords[0], coords[1], coords[2], coords[3], coords[4], coords[5]])
    if (output != expected):
        print "Test failed!\nInput: \t\t{0}\nExpected: \t{1}\nOutput: \t{2}".format(coords, expected.rstrip(), output)

file.close()

print "Test completed."

