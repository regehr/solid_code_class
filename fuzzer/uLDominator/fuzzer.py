import subprocess
import sys
import random
import decimal
import string

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
	
	#Test values in two's complement range
	for testInts in range(0, 1000):
		writer.write("printf(\"%i\\n\", " + str(testInts) + ");\n")
	
	#Min&Max values
	writer.write("printf(\"%i\\n\", " + str((2**31)-1) + ");\n")
	writer.write("printf(\"%i\\n\", " + str(-(2**31)) + ");\n")
	
	#Finish C file
	writer.write("exit(0);}\r\n")
	writer.close()
	
	print("Compiling and executing testIntegers.c")
	
	#Compile and execute
	subprocess.call(["musl/bin/musl-gcc", "-static", "testIntegers.c", "-w", "-o", "testIntegers"])
	proc = subprocess.Popen("./testIntegers", shell=True, stdout=subprocess.PIPE)
	fuzFile = open('testIntegers.txt', 'w')
	
	for line in proc.stdout:
		fuzFile.write(line)

	fuzFile.close()
	print("-----Finished executing testIntegers.c-----\n")
	
def testChars():
	print("-----Generating testChars.c-----")
	#Header of C file
	writer = open("testChars.c", "w")
	writer.write("#include <stdio.h>\r\n")
	writer.write("#include <stdlib.h>\r\n")
	writer.write("\r\n")
	writer.write("int main (int argc, const char *argv[])\r\n")
	writer.write("{\r\n")
	
	#Test values in two's complement range
	for testChars in range(32, 127):
		if(testChars != 39) and (testChars != 92) :
			writer.write("printf(\"%c\\n\", \'" + str(unichr(testChars)) + "\');\n")
	
	#Finish C file
	writer.write("exit(0);}\r\n")
	writer.close()
	
	print("Compiling and executing testChars.c")
	
	#Compile and execute
	subprocess.call(["musl/bin/musl-gcc", "-static", "testChars.c", "-w", "-o", "testChars"])
	proc = subprocess.Popen("./testChars", shell=True, stdout=subprocess.PIPE)
	
	fuzFile = open('testChars.txt', 'w')
	
	for line in proc.stdout:
		fuzFile.write(line)
		
	fuzFile.close()
	print("-----Finished executing testChars.c-----\n")
	
#data type range: 3.4E +/- 38
def testFloats():
	print("-----Generating testFloats.c-----")
	#Header of C file
	writer = open("testFloats.c", "w")
	writer.write("#include <stdio.h>\r\n")
	writer.write("#include <stdlib.h>\r\n")
	writer.write("\r\n")
	writer.write("int main (int argc, const char *argv[])\r\n")
	writer.write("{\r\n")
	
	#Test values in 32 bit range
	for testFloats in range(0, 1000):
		dec = decimal.Decimal(random.randrange(10000))/100
		writer.write("printf(\"%f\\n\", " + str(dec) + ");\n")
	
	#Min&Max values
	writer.write("printf(\"%f\\n\", " + str((3.4**38)) + ");\n")
	writer.write("printf(\"%f\\n\", " + str((3.4**(-38))) + ");\n")
	
	#Finish C file
	writer.write("exit(0);}\r\n")
	writer.close()
	
	print("Compiling and executing testFloats.c")
	
	#Compile and execute
	subprocess.call(["musl/bin/musl-gcc", "-static", "testFloats.c", "-w", "-o", "testFloats"])
	proc = subprocess.Popen("./testFloats", shell=True, stdout=subprocess.PIPE)
	
	fuzFile = open('testFloats.txt', 'w')
	
	for line in proc.stdout:
		fuzFile.write(line)
		
	fuzFile.close()
	print("-----Finished executing testFloats.c-----\n")
	
def testStrings():
	print("-----Generating testStrings.c-----")
	#Header of C file
	writer = open("testStrings.c", "w")
	writer.write("#include <stdio.h>\r\n")
	writer.write("#include <stdlib.h>\r\n")
	writer.write("\r\n")
	writer.write("int main (int argc, const char *argv[])\r\n")
	writer.write("{\r\n")
	
	#Test values with size = 10
	for testInts in range(0, 1000):
		testString = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(10))
		writer.write("printf(\"%s\\n\", \"" + str(testString) + "\");\n")

	
	#Finish C file
	writer.write("exit(0);}\r\n")
	writer.close()
	
	print("Compiling and executing testStrings.c")
	
	#Compile and execute
	subprocess.call(["musl/bin/musl-gcc", "-static", "testStrings.c", "-w", "-o", "testStrings"])
	proc = subprocess.Popen("./testStrings", shell=True, stdout=subprocess.PIPE)
	
	fuzFile = open('testStrings.txt', 'w')
	
	for line in proc.stdout:
		fuzFile.write(line)
		
	fuzFile.close()
	print("-----Finished executing testStrings.c-----\n")
	
def runAllWithGCC():
	print("-----Compiling and executing all .c files with GCC-----")
	#testInts
	subprocess.call(["gcc", "testIntegers.c", "-w", "-o", "gccIntegers"])
	proc = subprocess.Popen("./gccIntegers", shell=True, stdout=subprocess.PIPE)
	fuzFile = open('gccIntegers.txt', 'w')
	for line in proc.stdout:
		fuzFile.write(line)
		
	#testChars
	subprocess.call(["gcc", "testChars.c", "-w", "-o", "gccChars"])
	proc = subprocess.Popen("./gccChars", shell=True, stdout=subprocess.PIPE)
	fuzFile = open('gccChars.txt', 'w')
	for line in proc.stdout:
		fuzFile.write(line)
		
	#testFloats
	subprocess.call(["gcc", "testFloats.c", "-w", "-o", "gccFloats"])
	proc = subprocess.Popen("./gccFloats", shell=True, stdout=subprocess.PIPE)
	fuzFile = open('gccFloats.txt', 'w')
	for line in proc.stdout:
		fuzFile.write(line)
		
	#testStrings
	subprocess.call(["gcc", "testStrings.c", "-w", "-o", "gccStrings"])
	proc = subprocess.Popen("./gccStrings", shell=True, stdout=subprocess.PIPE)
	fuzFile = open('gccStrings.txt', 'w')
	for line in proc.stdout:
		fuzFile.write(line)
	print("-----Finished executing GCC compiled files-----\n")
	
def diffFiles():
	cmpFiles("testIntegers.txt", "gccIntegers.txt")
	cmpFiles("testChars.txt", "gccChars.txt")
	cmpFiles("testFloats.txt", "gccFloats.txt")
	cmpFiles("testStrings.txt", "gccStrings.txt")
	
def cmpFiles(file1, file2):
	print("-----Diff'ing "+file1+" with "+file2+"-----")
	output = ""
	output = output + subprocess.check_output(["diff", file1, file2])
	if(output != ""):
		print(file1+" and "+file2+" have differences!")
		print(output)
	print("-----Finished diff'ing-----\n")
	
def main():
	testIntegers()
	testChars()
	testFloats()
	testStrings()
	runAllWithGCC()
	diffFiles()

if __name__ == '__main__':
	main()
