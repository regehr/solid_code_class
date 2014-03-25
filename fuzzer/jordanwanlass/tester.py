import subprocess
import string
import random
import os
import filecmp
import sys

def createCFile(printMode, value):
	with open('testFile.c', 'w') as f:
		file.write("#include<stdio.h>\nint main(){return printf(\""+printMode+"\"," + str(value) + ");}")
		file.close()
		
def removeAllFiles():
	os.remove("testFile.c")
	os.remove("regularTest")
	os.remove("muslTest")
		

def execute():
	for i in range(-sys.maxint - 1, sys.maxint):
		makeCFile("%d", i)
		subprocess.call(["gcc", "test.c", "-o", "regularTest"])
		subprocess.call(["musl-gcc", "-static", "test.c", "-o", "muslTest"])
		
		with open("regularTest.txt", "w") as r:
			regular = subprocess.call(["./regularTest"], stdout=r)
		with open("muslTest.txt", "w") as m:
			musl = subprocess.call(["./muslTest"], stdout=m)
		
		if regular != musl or filecmp.cmp("regularTest.txt", "muslTest.txt") == False:
			print "GNU and Musl do not match up"
			exit()
	
	removeAllFiles()
	
	
	




execute()
