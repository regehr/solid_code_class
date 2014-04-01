import subprocess
import string
import random
import os
import filecmp
import sys

def include(f):
	f.write("#include<stdio.h>\n")
	f.write("#include \"musl.h\"\n")
	f.write("define LEN 10000\n")
	f.write("char buf[LEN];\n")
	
	
def beginMain(f):
	f.write("int main(){\n")

def addPrintf(f, mode, value):
	f.write("musl_snprintf (buf, LEN, \""+mode+"\","+str(value)+");\n")
	
def endMain(f):
	f.write("}\n")
	

def createRegular(mode, list, f):
	f.write("#include<stdio.h>\n")
	beginMain(f)
	for x in list:
		f.write("printf (\""+mode"\","+str(x)+");\n")
	endMain(f)

		
def removeAllFiles():
	os.remove("testFile.c")
	os.remove("regularTest")
	os.remove("muslTest")
		
def doRandInts():
	with open('testFile.c', 'w') as f:
		include(f)
		beginMain(f)
		mode = "%d"
		list = [];
		for i in range(1, 1000):
			randNum = random.randrange(-2147483646, 2147483647)
			addPrintf(f, mode, randNum)
			list.append(x)
		
	with open('regularTest.c', 'w') as f1:
		createRegular(mode, list, f1)
		
					
	subprocess.call(["gcc", "testFile.c", "-o", "muslTest"])
	subprocess.call(["gcc", "regularTest.c", "-o", "regularTest"])
	
	with open("regularTest.txt", "w") as r:
		regular = subprocess.call(["./regularTest"], stdout=r)
	with open("muslTest.txt", "w") as m:
		musl = subprocess.call(["./muslTest"], stdout=m)
		
	if regular != musl or filecmp.cmp("regularTest.txt", "muslTest.txt") == False:
		print "GNU and Musl do not match up"
		exit()	
		
def main():
	doRandInts()	
	removeAllFiles()
	

if __name__ == "__main__":
    main()