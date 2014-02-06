#!/user/bin/python

from subprocess import call
import os

#check where we're running from
if("test" in os.getcwd()):
    #if we're in the test folder, switch to main folder
    os.chdir("../")

#build the executable
call(["make"])

#move it to the test files folder
call(["cp", "huff", "test/testFiles"])

#clean up the root folder
call(["make", "clean"])

#switch to the test file folder
os.chdir("test/testFiles")

print "Testing..."

#for each file in the folder
for filename in os.listdir("."):
    #if it's a .txt file
    if(".txt" in filename):

        #get the table (saved as filename.tbl)
        writeTo = open(filename[:-4]+".tbl", "w")
        call(["./huff", "-t", filename], stdout=writeTo)
        writeTo.close()
        
        #make sure it's right (has 256 lines and each line is unique)
        readFrom = open(filename[:-4]+".tbl", "rb")
        uniqueLines = set()

        #for each line in the file
        for line in readFrom:

            #check to see if the line is already in the set
            if(line in uniqueLines):
                print "Duplicate encoding " + line + " in " + filename
            #if it's not already in the est
            else:
                #add it to the set
                uniqueLines.add(line)

        if(len(uniqueLines) != 257):
            print "Size of tree for " + filename + " is " + str(len(uniqueLines))
            """
        #compress the file
        call(["./huff", "-c", filename])
        
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
"""
print "Testing done"
