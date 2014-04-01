import subprocess
import sys
import random
import decimal
import os
import filecmp

#These lists taken from dsetser since his fuzzer.py looked cleaner than mine
formats = ["%d", "%lld", "%f", "%x", "%a"]
ranges = [lambda: random.randint(-2**31, (2**31)-1), \
           lambda: random.randint(-2**63, (2**63)-1), \
           lambda: random.uniform(-2**63, (2**63)-1), \
           lambda: random.randint(-2**31, (2**31)-1), \
           lambda: random.uniform(-2**63, (2**63)-1)]

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

#Generate 1000 print statements for each format.
#Uses musl-snprintf when parameter is true.
def fuzzer(useMusl):
	fuzz = ""
	for i in range(0, len(formats)):
		for c in range(0, 1000):
			test = ranges[i]()
			if(useMusl):
				fuzz += 'musl_snprintf(buf, LEN, "'+formats[i]+'\\n", '+str(test)+');\n'
				fuzz += 'printf("%s", buf);\n'
			else:
				fuzz += 'printf("'+formats[i]+'\\n", '+str(test)+');\n'
				
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
