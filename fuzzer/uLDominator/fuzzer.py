import subprocess
import sys
from random import randint

# %i or %d = int
# %c = char
# %f = float
# $s = string

def testIntegers():
	print("-----Generating testIntegers.c-----")
	#Header of C file
	writer = open("testIntegers.c", "w")
	writer.write("#include <stdio.h>\r\n")
	writer.write("#include <stdlib.h>\r\n")
	writer.write("\r\n")
	writer.write("int main (int argc, const char *argv[])\r\n")
	writer.write("{\r\n")
	
	oracleList = []
	
	#Test values in two's complement range
	for testInts in range(0, 1000):
		writer.write("printf(\"%i\\n\", " + str(testInts) + ");\n")
		oracleList.append(str(testInts))

	
	#Min&Max values
	writer.write("printf(\"%i\\n\", " + str((2**31)-1) + ");\n")
	writer.write("printf(\"%i\\n\", " + str(-(2**31)) + ");\n")
	oracleList.append(str((2**31)-1))
	oracleList.append(str(-(2**31)))
	
	#Finish C file
	writer.write("exit(0);}\r\n")
	writer.close()
	
	print("Compiling and executing testIntegers.c")
	
	#Compile and execute
	subprocess.call(["musl/bin/musl-gcc", "-static", "testIntegers.c", "-w", "-o", "testIntegers"])
	proc = subprocess.Popen("./testIntegers", shell=True, stdout=subprocess.PIPE)
	
	#Print non-empty output
	out, err = proc.communicate()
	listOut = filter(None, out.split('\n'))
	if(listOut != oracleList) :
		print("Error in strings returned from testIntegers.c")
	print("-----Finished executing testIntegers.c-----")
	
def testChars():
	print("-----Generating testChars.c-----")
	#Header of C file
	writer = open("testChars.c", "w")
	writer.write("#include <stdio.h>\r\n")
	writer.write("#include <stdlib.h>\r\n")
	writer.write("\r\n")
	writer.write("int main (int argc, const char *argv[])\r\n")
	writer.write("{\r\n")
	
	oracleList = []
	
	#Test values in two's complement range
	for testChars in range(32, 127):
		if(testChars != 39) and (testChars != 92) :
			writer.write("printf(\"%c\\n\", \'" + str(unichr(testChars)) + "\');\n")
			oracleList.append(str(unichr(testChars)))
	
	#Finish C file
	writer.write("exit(0);}\r\n")
	writer.close()
	
	print("Compiling and executing testChars.c")
	
	#Compile and execute
	subprocess.call(["musl/bin/musl-gcc", "-static", "testChars.c", "-w", "-o", "testChars"])
	proc = subprocess.Popen("./testChars", shell=True, stdout=subprocess.PIPE)
	
	#Print non-empty output
	out, err = proc.communicate()
	listOut = filter(None, out.split('\n'))
	if(listOut != oracleList) :
		print("Error in strings returned from testChars.c")
	print("-----Finished executing testChars.c-----")
	
def testFloats():
	print("Todo")
	
def testStrings():
	print("Todo")
	
def testCombinations():
	print("Todo")
	
def main():
	testIntegers()
	testChars()
	testFloats()
	testStrings()
	testCombinations()

if __name__ == '__main__':
	main()
