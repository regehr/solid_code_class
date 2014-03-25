from subprocess import CalledProcessError, check_output
import os

def newFile(fileName):
	file = open(fileName , 'w')
	return file

def writeMain(file):
	file.write("#include <stdio.h>\n")
	file.write("int main(int argc, char **argv){\n")

def writePrint(file, printType, printValue):
	file.write("printf(\"%" + printType + "\" , " + str(printValue) + ");\n");

def writeClose(file):
	file.write("return 0;\n}")
	file.close()

def populateFileList(fileList , fileBase , numberOfFiles):
	for i in range(numberOfFiles):
		fileList.append(fileBase + str(i) + ".c")
	return fileList

def populatePrintTypeDic(toPopulate):
	toPopulate = {'c':['\'c\''] , 'e':[123e+25] , 'g':[123.25]}
	count = 0.0;
	listToAdd = list()

	for i in range(100):
		num = i + count
		listToAdd.append(num)
		count += .1

	toPopulate['d'] = listToAdd
	toPopulate['f'] = listToAdd

	listToAdd = list()
	count = 0;
	for i in range(100):
		listToAdd.append(count)
		count = count + 1000;

	toPopulate['o'] = listToAdd
	toPopulate['x'] = listToAdd
	toPopulate['u'] = listToAdd

	#print toPopulate
	return toPopulate

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
		compileFile(file)
		compileFileGcc(file)

def compileFile(fileName):
	try:
		check_output(["./muslInstall/bin/musl-gcc" , fileName , "-o" , fileName[:-2] , "-static"])
	except CalledProcessError as e:
		print e

def compileFileGcc(fileName):
	try:
		check_output(["gcc" , fileName , "-o" , fileName[:-2] + "gcc"])
	except CalledProcessError as e:
		print e

def runFiles(fileList, printTypeDic , logfile):

	newList = list()
        for key in printTypeDic:
                for i in printTypeDic[key]:
                        newList.append((key , i))


	for file,i in zip(fileList,newList):
		output = "";
		outputGcc = "";
		try:
                	output = check_output(file[:-2])
			outputGcc = check_output(file[:-2] + "gcc")
        	except CalledProcessError as e:
                	print e.returncode
			print e.message
			print e

		if(output != outputGcc):
			logfile.write("print failed! expected = " + output + " actual = " + outputGcc + "file = \n" + file + "\n")
			logfile.write("printf params = " + str(i[0]) + " " + str(i[1]) + "\n" + "\n")


def removeFiles(fileList):
	for file in fileList:
		check_output(["rm" , file , file[:-2] , file[:-2]+"gcc"])
	
def main():
	fileBase = os.getcwd() + "/" + "testFile"
	fileList = list()
	printTypeDic = {}
	printTypeDic = populatePrintTypeDic(printTypeDic)

	logFile = newFile("logfile")

	numberOfFiles = 0

	for key in printTypeDic:
		for i in printTypeDic[key]:
			numberOfFiles = numberOfFiles + 1

	fileList = populateFileList(fileList , fileBase , numberOfFiles)

	writeFiles(fileList , printTypeDic)

	compileFiles(fileList)

	runFiles(fileList , printTypeDic , logFile)

	removeFiles(fileList)


if __name__ == "__main__":
	main()

