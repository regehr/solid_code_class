#!/usr/bin/env python27
import os
from subprocess import call


#Function to find the number of elements in the file
def file_len(fileName):
	with open(fileName) as f:
		f.seek(0, 2)    # Seek to the end of the file
		return f.tell()

#Function to ensure all elements are unique 		
def unique(filename):
	with open(filename) as f:
		seen = set()
		for line in f:
			if line in seen:
				print "Error. Contains Duplicate " + line
			else:
				seen.add(line)

#Generate and print a translation table for a non .huff file(.txt)
#Check for correct length and uniqueness
#Check memory leaks using Valgrind			
def test1():
	#Run make
	call(["make"])

	#Create a file with 256 ASCII characters
	writeTo = open("testFile.txt", "w")
	for element in range(0,256):
		writeTo.write(chr (element))
	writeTo.close()

	#Dump to table
	writeTo = open("table", "w")
        
	call(["./huff", "-t", "testFile.txt"], stdout = writeTo)
	call(["valgrind", "--leak-check=yes", "./huff", "-t", "testFile.txt"])

	#Check that the file has 256 lines
	mylen = file_len("table")
	if mylen != 256:
		print "File should be 256 lines. Actual " + str(mylen)

	#Check that they are all unique
	unique("table")
	
def test2():
    print "In progress"


def test3():
    print "In progress"

def test4():
    print "In progress"
			
if __name__ == "__main__":

	#Test ./huff -t filename.txt
	test1()
	#Test ./huff -t filename.huff
	test2()
	#Test ./huff -c filename.txt
	test3()
	#Test ./huff -d filename.huff
	test4()



