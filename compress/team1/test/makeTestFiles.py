#!/bin/usr/python

from random import randint
import os
import subprocess

#check the current working directory
if("test" not in os.getcwd()):
    os.chdir("test")

#make sure the directory for the test files is there
if(not os.path.exists("./testFiles")):
    subprocess.call(["mkdir", "./testFiles"])

#set up a file to write to
fh = open("testFiles/allChars.txt", "w");

#an array to hold all char values
charValues = []

#write all ASCII characters
for charCode in range(0, 256):
    fh.write(chr(charCode))
    charValues.append(chr(charCode))

fh.write("\n")
fh.close()

#make copies then add a character a-z to each respective copy
for charCode in range(0, 256):
    
    #name the new file
    fh = open("testFiles/allChars_"+str(charCode)+".txt", "w")
    
    #for each of the characters we have
    for elem in charValues:
        
        #if this one matches the charCode we're on
        if(elem == chr(charCode)):
            
            #write them both
            fh.write(elem)
            fh.write(chr(charCode))
            
        #if it doesn't match up
        else:
            #just write this one
            fh.write(elem)
    fh.write("\n")
    fh.close()

fh = open("testFiles/gibberish.txt", "w")    
        
#generate one of complete gibberish
for numberOfChars in range(0, 1024):
    fh.write(chr(randint(0, 255)))
fh.write("\n")
