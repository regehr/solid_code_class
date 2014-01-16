# Modeled after domfurano's test script (including test.txt)
import subprocess

print "Beginning test.\n"

i = 0

file = open("test.txt", "r")

for line in file:
    coords = line
    expected = file.next()
    cmd = "./triangle " + str(coords)
    p = subprocess.Popen(cmd, stderr=subprocess.STDOUT, stdout=subprocess.PIPE, shell=True)
    result = p.communicate()[0]
    print "expected is : " +str(expected) + "result is : "+str(result)
    if result == expected:
       i+=1

file.close()

print "Number correct : "+str(i)+"/15"
print "Test completed."

