#!/user/bin/python

from subprocess import call
import os

#switch to the main folder
os.chdir("../")

#build the executable
call(["make"])

#move it to the test files folder
call(["cp", "huff", "test/testFiles"])

#clean up the root folder
call(["make", "clean"])

#switch to the test file folder
os.chdir("test/testFiles")

#for each file in the folder
for filename in os.listdir("."):
    if(".txt" in filename):
        #compress the file
        call(["./huff", "-c", filename])

    #get the table (saved as filename.comp)
    call(["./huff", "-t", filename, ">>", filename[:-4]+".comp")]
    
#make sure it's right
    
#print out if correct or wrong
    
#read in the original file
originalFile = open(filename, "r")
originalText = []

for line in originalFile:
    originalText.append(line)

#uncompress the file
    call(["./huff", "-d", filename[:-4]+".huff"])

#read in the uncompressed version
uncompressedFile = open(filename[:-4], "r")
uncompressedText = []

for line in uncompressedFile:
    uncompressedText.append(line)
    
#make sure the uncompressed file matches the original
print filename
print originalText == uncompressedText
