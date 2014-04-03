import subprocess
import sys
import random
import decimal
import os
import filecmp
import string

#These lists taken from dsetser since his fuzzer.py looked cleaner than mine
formats = ["d", "i", "u", "lld", "f", "F", "o", "x", "X", "a", "A", "e", "E", "g", "G", "s", "c", "lu", "hu"]
ranges = [lambda: random.randint(-2147483647, 2147483647), \
           lambda: random.randint(-2147483647, 2147483647), \
           lambda: random.randint(0, 2147483647), \
           lambda: random.randint(-9223372036854775807, 9223372036854775807), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: random.randint(-32767, 32767), \
           lambda: random.randint(-32767, 32767), \
           lambda: random.randint(-32767, 32767), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: '"' + createString() + '"', \
           lambda: "'" + str(random.choice(string.ascii_letters)) + "'", \
           lambda: random.randint(0, 4294967295), \
           lambda: random.randint(0, 65535)]
           
def createString():
	createString = ""
	for i in range(0, random.randint(0, 100)):
		char = str(random.choice(string.ascii_letters + string.digits))
		if char != "%":
			createString += char
	return createString
	
def createFormat():
	index = random.randint(0, len(formats)-1)
	formatString = "%" + formats[index]
	args = str(ranges[index]())
	for i in range(0, random.randint(1, 15)):
		padding = createString()
		index = random.randint(0, len(formats)-1)
		formatString += padding + "%" + prefix(formats[index]) + formats[index]
		args += ", " + str(ranges[index]())
	return {'format':formatString, 'args':args}
	
def prefix(formatString):
	prefixesAllowed = ["d", "i", "o", "x", "X", "a", "A", "f", "F"]
	prefix = ""
	rand = random.randint(0, 10)
	if(rand < 5 or formatString not in prefixesAllowed):
		return ""
	# Flag
	rand = random.randint(0, 10)
	if rand == 1:
		prefix += "-"
	if rand == 2:
		prefix += "+"
	if rand == 3:
		prefix += " "
	if rand == 4:
		prefix += "0"
	# Width
	rand = random.randint(0, 5)
	if rand == 1:
		prefix += str(random.randint(1, 20))
	# Precision
	rand = random.randint(0, 5)
	if rand == 1:
		prefix += str(random.randint(1, 20))
	return prefix

#Copy files from standalone to current directory.
def cloneFiles():
	os.system("cp ../musl-printf-standalone/*.c .")
	os.system("cp ../musl-printf-standalone/*.h .")
	
#Generate two c files, one using musl and the other gcc.
#If using coverage parameters then compile them using the coverage options.
def generateFiles():
	seed = random.random()
	files = ["gcc-version", "musl-version"]
	for f in files:
		print("Generating "+f+".c")
		random.seed(seed)
		newFile = open('test-printf.c', 'w')
		newFile.write(generateCFile(f == "musl-version"))
		newFile.close()
		if(len(sys.argv) == 2 and sys.argv[1] == "coverage"):
			os.system("make c-coverage &> /dev/null")
		else:
			os.system("make test-printf &> /dev/null")
		subprocess.call(["mv", "a.out", f])

#Generate header of a fuzzing c file.
def generateCFile(useMusl):
	cFile  = '#include <stdio.h>\n'
	cFile += '#include <stdlib.h>\n'
	cFile += '#include <string.h>\n'
	if(useMusl):
		cFile += '#include <stdarg.h>\n'
		cFile += '#include "musl.h"\n'
		cFile += '#define LEN 10000\n'
		cFile += 'char buf[LEN];\n'
	cFile += 'int main(int argc, char* argv[]){\n'
	cFile += fuzzer(useMusl)
	cFile += 'return 0;\n}'
	return cFile

#Generate 5000 print statements.
#Uses musl-snprintf when parameter is true.
def fuzzer(useMusl):
	fuzz = ""
	for i in range(0, 5000):
		form = createFormat()
		string = form.get('format')
		value = form.get('args')
		if(useMusl):
			fuzz += 'musl_snprintf(buf, LEN, "'+string+'\\n", '+value+');\n'
			fuzz += 'printf("%s", buf);\n'
		else:
			fuzz += 'printf("'+string+'\\n", '+value+');\n'				
	return fuzz
	
#Runs both compiled files, tests the outputs for equality.
def testFiles():
	musl = subprocess.check_output("./musl-version")
	gcc  = subprocess.check_output("./gcc-version")
	if(musl != gcc):
		print("File output mismatch!")
	else:
		print("Files match.")

#Remove all copied or generated files from current directory.	
def removeFiles():
	if(len(sys.argv) != 2 or sys.argv[1] != "coverage"):
		os.system('rm *.c')
		os.system('rm *.h')
	os.remove('musl-version')
	os.remove('gcc-version')

def main():
	cloneFiles()
	generateFiles()
	testFiles()
	removeFiles()

if __name__ == '__main__':
	main()
