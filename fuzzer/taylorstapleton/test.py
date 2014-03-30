from subprocess import CalledProcessError, check_output
import os
import random


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

def writePrintMusl(file, printType, printValue):
	file.write("musl_snprintf (buf, LEN, \"%" + printType + "\" , " + str(printValue) + ");\n");
	file.write("printf(\"%s\", buf);")

def writePrint(file, printType, printValue):
        file.write("printf (\"%" + printType + "\" , " + str(printValue) + ");\n");

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
		check_output(["gcc" , fileName , "-o", fileName[:-2] + "gcc", "-I " + os.getcwd()])# "fwrite.c" , "snprintf.c" , "vfprintf.c" , "vsnprintf.c" , "-o" , fileName[:-2] + "gcc"])
	except CalledProcessError as e:
		print e

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
			logfile.write("print failed! expected = " + output + " actual = " + outputGcc + "file = \n" + file + "\n")
			logfile.write("printf params = " + str(testCase[0]) + " " + str(testCase[1]) + "\n" + "\n")
		else:
			logfile.write("passed " + str(testCase[0]) + " " + str(testCase[1]) + "\n")


def removeFiles(fileList):
	for file in fileList:
		check_output(["rm" , file , file[:-2] , file[:-2]+"gcc"])

def createTestCase():
	randomNumber = random.randint(0,8)
	testCase = ["",""]
	
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
                testCase[0] = "u"
                testCase[1] = str(random.getrandbits(31))




	return testCase	
	
def main():
	logFile = newFile("logfile")
	n = 0
	while(True):
		n = n + 1	
		print n
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
		writePrintMusl(fileMusl, testCase[0], testCase[1])
		writePrint(file, testCase[0], testCase[1])

		#close the files
		writeClose(fileMusl)
		writeClose(file)

		compileFiles([fileNameMusl + ".c", fileName + ".c"])
	
		runFiles([fileName] , testCase , logFile)
	
		#removeFiles(fileList)

if __name__ == "__main__":
	main()

