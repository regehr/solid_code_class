#!/usr/bin/env python27
import os
from subprocess import call
import filecmp
import shutil

def line_count(fileName):
	with open(fileName) as f:
		return f.read().count("\n")

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
	#call(["make"])

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
	mylen = line_count("table")
	if mylen != 256:
		print "File should be 256 lines. Actual " + str(mylen)

	#Check that they are all unique
	unique("table")

#Compress .txt file
def test2():
	call(["./huff", "-c", "testFile.txt"])
	os.path.exists("testFile.txt.huff")

#Display contents of .huff to terminal
def test3():

	writeTo = open("compressedTable", "w")
	call(["./huff", "-t", "testFile.txt.huff"])
	print '----------------------------------------------'
	print writeTo

#Compress .huff file
def test4():
	call(["./huff", "-c", "testFile.txt.huff"])
	os.path.exists("testFile.txt.huff.huff")

#Decompress .huff.huff file
def test5():
	call(["rm", "-f", "testFile.txt.huff"])
	call(["./huff", "-d", "testFile.txt.huff.huff"])
	os.path.exists("testFile.txt.huff")

#Test for file equality before and after compression/decompression
def test6():
	writeTo = open("compareTest.txt", "w")
	for element in range(0,256):
		writeTo.write(chr (element))
	writeTo.close()
	shutil.copy('compareTest.txt', 'test.txt')
	call(["./huff", "-c", "compareTest.txt"])
	call(["./huff", "-d", "compareTest.txt.huff"])
	if not (filecmp.cmp("compareTest.txt", "test.txt")):
		print "test6 fail"
	



if __name__ == "__main__":

	#Test ./huff -t filename.txt checking proper length and uniqueness
	test1()
	#Test ./huff -c filename.txt
	test2()
	#Test ./huff -t filename.txt.huff
	test3()
	#Test ./huff -c filename.txt.huff
	test4()
	#Test ./huff -d filename.txt.huff
	test5()
	#Test to see if the contents of a file remain the same
	#after it is compressed and decompressed
	test6()



