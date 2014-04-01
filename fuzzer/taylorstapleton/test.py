from subprocess import CalledProcessError, check_output
import os
import random
import sys


def newFile(fileName):
	file = open(fileName , 'w')
	return file

def writeMainMusl(file):
	file.write("#include <stdio.h>\n")
	file.write("#include <stdarg.h>\n")
	file.write("#include \"musl.h\"\n")
	file.write("#define LEN 10000\n")
	file.write("char buf[LEN];\n")
	file.write("int main(void){\n")

def writeMain(file):
        file.write("#include <stdio.h>\n")
        file.write("int main(void){\n")

def writePrintMusl(file, printType, printValue, printOpt):
	file.write("musl_snprintf (buf, LEN, \"%" + printOpt + printType + "\" , " + str(printValue) + ");\n");
	file.write("printf(\"%s\", buf);")

def writePrint(file, printType, printValue, printOpt):
        file.write("printf (\"%" + printOpt + printType + "\" , " + str(printValue) + ");\n");

def writeClose(file):
	file.write("return 0;\n}")
	file.close()

def populateFileList(fileList , fileBase , numberOfFiles):
	for i in range(numberOfFiles):
		fileList.append(fileBase + str(i) + ".c")
	return fileList

def writeFiles(fileList , printTypeDic):
	newList = list()
	for key in printTypeDic:
		for i in printTypeDic[key]:
			newList.append((key , i))

	for file,printType in zip(fileList , newList):
		currentFile = newFile(file)
		writeMain(currentFile)
		writePrint(currentFile , printType[0] , printType[1])
		writeClose(currentFile)

def compileFiles(fileList):
	for file in fileList:
		compileFileGcc(file)

def compileFileGcc(fileName):
	try:
		if(check_output(["gcc" , fileName , "-o", fileName[:-2] + "gcc" , "fwrite.o" , "snprintf.o" , "vfprintf.o" , "vsnprintf.o" , "-o" , fileName[:-2] + "gcc", "-lgcov"]) != ""):
			sys.exit("")
		
	except CalledProcessError as e:
		print e
		sys.exit("")

def runFiles(fileList, testCase , logfile):

	for file in fileList:
		output = "";
		outputGcc = "";
		try:
                	output = check_output(file + "gcc")
			outputGcc = check_output(file + "Musl" + "gcc")
        	except CalledProcessError as e:
                	print e.returncode
			print e.message
			print e

		if(output != outputGcc):
			logfile.write("print failed! expected = " + output + " actual = " + outputGcc + "\n")
			logfile.write("printf params = " + str(testCase[0]) + " " + str(testCase[1]) + " " + str(testCase[2]) + "\n" + "\n")
			return False
		else:
			logfile.write("passed " + str(testCase[0]) + " " + str(testCase[1]) + " " + str(testCase[2]) + " " + " musl output = " + outputGcc + " reg output = " + output + "\n")
	return True


def removeFiles(fileList):
	for file in fileList:
		check_output(["rm" , file , file[:-2] , file[:-2]+"gcc"])

def createTestCase():
	randomNumber = random.randint(0,61)
	testCase = ["","",""]
	
	if(randomNumber == 0):
		testCase[0] = "d"
		testCase[1] = str(random.getrandbits(31))
	elif(randomNumber == 1):
                testCase[0] = "o"
                testCase[1] = str(random.getrandbits(31))
	elif(randomNumber == 2):
                testCase[0] = "x"
                testCase[1] = str(random.getrandbits(31))
	elif(randomNumber == 3):
                testCase[0] = "s"
                testCase[1] = "\"" + str(random.getrandbits(100)) + "\""
	elif(randomNumber == 4):
		testCase[0] = "f"
		testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
        elif(randomNumber == 5):
                testCase[0] = "X"
                testCase[1] = str(random.getrandbits(31))
        elif(randomNumber == 6):
                testCase[0] = "i"
                testCase[1] = str(random.getrandbits(31))
        elif(randomNumber == 7):
                testCase[0] = "F"
		testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
	elif(randomNumber == 8):
                testCase[0] = "dhh"
                testCase[1] = str(random.getrandbits(8))
	elif(randomNumber == 9):
                testCase[0] = "u"
                testCase[1] = str(random.getrandbits(31))
	elif(randomNumber == 10):
                testCase[0] = "dh"
                testCase[1] = str(random.getrandbits(16))
	elif(randomNumber == 11):
                testCase[0] = "dl"
                testCase[1] = str(random.getrandbits(32))
        elif(randomNumber == 12):
                testCase[0] = "dll"
                testCase[1] = str(random.getrandbits(63))
        elif(randomNumber == 13):
                testCase[0] = "ihh"
                testCase[1] = str(random.getrandbits(8))
        elif(randomNumber == 14):
                testCase[0] = "ih"
                testCase[1] = str(random.getrandbits(16))
        elif(randomNumber == 15):
                testCase[0] = "il"
                testCase[1] = str(random.getrandbits(32))
        elif(randomNumber == 16):
                testCase[0] = "ill"
                testCase[1] = str(random.getrandbits(63))
	elif(randomNumber == 17):
                testCase[0] = "fl"
                testCase[1] = str(random.getrandbits(30)) + "." + str(random.getrandbits(30))
        elif(randomNumber == 18):
                testCase[0] = "fL"
                testCase[1] = str(random.getrandbits(30)) + "." + str(random.getrandbits(30))
        elif(randomNumber == 19):
                testCase[0] = "F"
                testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
        elif(randomNumber == 20):
                testCase[0] = "Fl"
                testCase[1] = str(random.getrandbits(30)) + "." + str(random.getrandbits(30))
        elif(randomNumber == 21):
                testCase[0] = "FL"
                testCase[1] = str(random.getrandbits(30)) + "." + str(random.getrandbits(30))
        elif(randomNumber == 22):
                testCase[0] = "c"
                testCase[1] = str(random.getrandbits(8))
        elif(randomNumber == 23):
                testCase[0] = "xhh"
                testCase[1] = str(random.getrandbits(8))
        elif(randomNumber == 24):
                testCase[0] = "xh"
                testCase[1] = str(random.getrandbits(16))
        elif(randomNumber == 25):
                testCase[0] = "xl"
                testCase[1] = str(random.getrandbits(32))
        elif(randomNumber == 26):
                testCase[0] = "xll"
                testCase[1] = str(random.getrandbits(63))
        elif(randomNumber == 27):
                testCase[0] = "u"
                testCase[1] = str(random.getrandbits(32))
        elif(randomNumber == 28):
                testCase[0] = "uh"
                testCase[1] = str(random.getrandbits(8))
        elif(randomNumber == 29):
                testCase[0] = "uhh"
                testCase[1] = str(random.getrandbits(16))
        elif(randomNumber == 30):
                testCase[0] = "ul"
                testCase[1] = str(random.getrandbits(32))
        elif(randomNumber == 31):
                testCase[0] = "ull"
                testCase[1] = str(random.getrandbits(63))
        elif(randomNumber == 32):
                testCase[0] = "e"
                testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
        elif(randomNumber == 33):
                testCase[0] = "E"
                testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
        elif(randomNumber == 34):
                testCase[0] = "a"
                testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
        elif(randomNumber == 35):
                testCase[0] = "A"
                testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
        elif(randomNumber == 36):
                testCase[0] = "el"
                testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
        elif(randomNumber == 37):
                testCase[0] = "eL"
                testCase[1] = str(random.getrandbits(30)) + "." + str(random.getrandbits(30))
        elif(randomNumber == 38):
                testCase[0] = "al"
                testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
        elif(randomNumber == 39):
                testCase[0] = "aL"
                testCase[1] = str(random.getrandbits(30)) + "." + str(random.getrandbits(30))
        elif(randomNumber == 40):
                testCase[0] = "El"
                testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
        elif(randomNumber == 41):
                testCase[0] = "EL"
                testCase[1] = str(random.getrandbits(30)) + "." + str(random.getrandbits(30))
        elif(randomNumber == 42):
                testCase[0] = "Al"
                testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
        elif(randomNumber == 43):
                testCase[0] = "AL"
                testCase[1] = str(random.getrandbits(30)) + "." + str(random.getrandbits(30))
        elif(randomNumber == 44):
                testCase[0] = "g"
                testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
        elif(randomNumber == 45):
                testCase[0] = "gl"
                testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
        elif(randomNumber == 46):
                testCase[0] = "gL"
                testCase[1] = str(random.getrandbits(30)) + "." + str(random.getrandbits(30))
        elif(randomNumber == 47):
                testCase[0] = "G"
                testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
        elif(randomNumber == 48):
                testCase[0] = "Gl"
                testCase[1] = str(random.getrandbits(15)) + "." + str(random.getrandbits(15))
        elif(randomNumber == 49):
                testCase[0] = "GL"
                testCase[1] = str(random.getrandbits(30)) + "." + str(random.getrandbits(30))
        elif(randomNumber == 50):
                testCase[0] = "ohh"
                testCase[1] = str(random.getrandbits(8))
        elif(randomNumber == 51):
                testCase[0] = "oh"
                testCase[1] = str(random.getrandbits(16))
        elif(randomNumber == 52):
                testCase[0] = "ol"
                testCase[1] = str(random.getrandbits(32))
        elif(randomNumber == 53):
                testCase[0] = "oll"
                testCase[1] = str(random.getrandbits(63))
        elif(randomNumber == 54):
                testCase[0] = "xhh"
                testCase[1] = str(random.getrandbits(8))
        elif(randomNumber == 55):
                testCase[0] = "xh"
                testCase[1] = str(random.getrandbits(16))
        elif(randomNumber == 56):
                testCase[0] = "xl"
                testCase[1] = str(random.getrandbits(32))
        elif(randomNumber == 57):
                testCase[0] = "xll"
                testCase[1] = str(random.getrandbits(63))
        elif(randomNumber == 58):
                testCase[0] = "Xhh"
                testCase[1] = str(random.getrandbits(8))
        elif(randomNumber == 59):
                testCase[0] = "Xh"
                testCase[1] = str(random.getrandbits(16))
        elif(randomNumber == 60):
                testCase[0] = "Xl"
                testCase[1] = str(random.getrandbits(32))
        elif(randomNumber == 61):
                testCase[0] = "Xll"
                testCase[1] = str(random.getrandbits(63))
        elif(randomNumber == 62):
                testCase[0] = "S"
                testCase[1] = str(random.getrandbits(32))
        elif(randomNumber == 63):
                testCase[0] = "C"
                testCase[1] = str(random.getrandbits(8))



	randomOper = random.randint(0,1)
	if(randomOper == 1):
		testCase[2] = testCase[2] + "-"

        randomOper = random.randint(0,1)
        if(randomOper == 1):
                testCase[2] = testCase[2] + "+"

        randomOper = random.randint(0,1)
        if(randomOper == 1):
                testCase[2] = testCase[2] + " "

        randomOper = random.randint(0,1)
        if(randomOper == 1):
                testCase[2] = testCase[2] + "#"


	return testCase	
	
def main():
	logFile = newFile("logfile")
	n = 0
	failedTests = 0
	while(True):
		n = n + 1
		fileNameMusl = os.getcwd() + "/" + "testFileMusl"
		fileName = os.getcwd() + "/" + "testFile"

		testCase = createTestCase()

		#call newFile with both
		fileMusl = newFile(fileNameMusl + ".c")
		file = newFile(fileName + ".c")
	
		# write main
		writeMainMusl(fileMusl)
		writeMain(file)

		#write the body
		writePrintMusl(fileMusl, testCase[0], testCase[1], testCase[2])
		writePrint(file, testCase[0], testCase[1], testCase[2])

		#close the files
		writeClose(fileMusl)
		writeClose(file)

		compileFiles([fileNameMusl + ".c", fileName + ".c"])
	
		if(runFiles([fileName] , testCase , logFile) != True):
			print "failed test " + str(n)
			failedTests= failedTests + 1
		else:
			print "passed test " + str(n)
	
		#removeFiles(fileList)
		if(n % 100 == 0):
			print "coverage results so far:\n"
			print os.system("gcov vfprintf.c")
			print "failed tests = " + str(failedTests)

if __name__ == "__main__":
	main()

