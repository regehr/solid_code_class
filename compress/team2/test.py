#!/usr/bin/env python27
import os
from subprocess import call


#Run make
call(["make"])

#Create a file with 256 ascii characters
writeTo = open("testFile.txt", "w")
for element in range(0,256):
    writeTo.write(chr (element))
writeTo.close()

writeTo = open("table", "w")
        
call(["./huff", "-t", "testFile.txt"], stdout = writeTo)

call(["valgrind", "--leak-check=yes", "./huff", "-t", "testFile.txt"])


#Check that the file has 256 lines
def file_len(fileName):
    with open(fileName) as f:
        for i, l in enumerate(f):
            pass
        return i + 1

mylen = file_len("table")
if mylen != 256:
    print "File should be 256 lines. Actual " + str(mylen)


#Check that they are all unique
with open("table") as f:
    seen = set()
    for line in f:
        if line in seen:
            print "Error. Contains Duplicate " + line
        else:
            seen.add(line)



