#!/bin/usr/python

from random import randint

#set up a file to write to
fh = open("testFiles/allChars.txt", "w");

#an array to hold all char values
charValues = []

#write all characters a-z
for charCode in range(97, 123):
    fh.write(str(unichr(charCode)))
    charValues.append(str(unichr(charCode)))

fh.write("\n")
fh.close()

#make copies then add a character a-z to each respective copy
for charCode in range(97, 123):
    
    #name the new file
    fh = open("testFiles/allChars_"+str(unichr(charCode))+".txt", "w")
    
    #for each of the characters we have
    for elem in charValues:
        
        #if this one matches the charCode we're on
        if(elem == str(unichr(charCode))):
            
            #write them both
            fh.write(elem)
            fh.write(str(unichr(charCode)))
            
        #if it doesn't match up
        else:
            #just write this one
            fh.write(elem)
    fh.write("\n")
    fh.close()

fh = open("testFiles/gibberish.txt", "w")    
        
#generate one of complete gibberish
for numberOfChars in range(0, 100):
    fh.write(str(unichr(randint(97, 122))))
fh.write("\n")
