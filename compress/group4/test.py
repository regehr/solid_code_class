import sys
import subprocess
import os



class oneTest():
	testNum = 0
	fileName = ""
	moq = 1
	programName = ""
	messgae = ""
	type = ""

	def __init__(self , prog , file , test , moq , mess , type):
		self.testNum = test
		self.fileName = file
		self.moq = moq
		self.programName = prog
		self.message = mess
		self.type = type

def makeTest(prog , file , test , moq , message , type):
	test = oneTest(prog , file , test , moq , message , type)
	return test


def successTest(programName , fileName , testNum , moq , type):
	try:
		if(moq == 1):
			output = subprocess.check_output([os.getcwd() + "/" + programName , fileName , "0"])
		else:
			output = subprocess.check_output([os.getcwd() + "/" + programName , type , fileName])

	except subprocess.CalledProcessError, e:
		return testNum

	return 0

def failureTest(programName , fileName , testNum , moq , type):
	try:
		if(moq == 1):
			output = subprocess.check_output([os.getcwd() + "/" + programName , fileName , "1"])
		else:
			output = subprocess.check_output([os.getcwd() + "/" + programName , type , fileName])

	except subprocess.CalledProcessError, e:
		return 0

	return testNum

def makeFile(fileName , length , fileList):
	file = open(os.getcwd() + "/" + fileName , "w+")
	for i in range(0 , length):
		file.write(str(i))

	fileList.append(fileName)
	return fileName

def main():
	# moq enabled for testing the tester
	moq = 0;
	moq2 = 1;
	moqTesterName = "test.o"

	results = list()
	successList = list()
	failureList = list()
	fileList = list()


	successList.append(makeTest(sys.argv[1] , makeFile("test0file" , 2000000 , fileList) , 0 , moq , "large file success test failed" , "-t"))
	successList.append(makeTest(sys.argv[1] , makeFile("test1file" , 0 , fileList) , 1 , moq , "empty file test failed" , "-t"))
	successList.append(makeTest(sys.argv[1] , makeFile("test2file" , 1024 , fileList) , 2 , moq , "medium size file failed" , "-t"))
	failureList.append(makeTest(sys.argv[1] , "badFile" , 3 , moq , "bad filename test failed" , "-t"))
	failureList.append(makeTest(sys.argv[1] , "" , 4 , moq , "no argument test failed" , "-t"))

	
        successList.append(makeTest(moqTesterName , makeFile("test3file" , 2000000 , fileList) , 5 , moq2 , "moq large file test failed" , "-t"))
        successList.append(makeTest(moqTesterName , makeFile("test4file" , 0 , fileList) , 6 , moq2 , "moq empty file test failed" , "-t"))
        successList.append(makeTest(moqTesterName , makeFile("test5file" , 1024 , fileList) , 7 , moq2 , "moq regular file test failed" , "-t"))
        failureList.append(makeTest(moqTesterName , "badFile" , 8 , moq2 , "moq bad file name test failed" , "-t"))
        failureList.append(makeTest(moqTesterName , "" , 9 , moq2 , "moq incorrect arguments failed" , "-t"))



	for test in successList:
		results.append(successTest(test.programName , test.fileName , test.testNum , test.moq , test.type))	

	for test in failureList:
		results.append(failureTest(test.programName , test.fileName , test.testNum , test.moq , test.type))

	totalTests = list()
	for test in successList:
		totalTests.append(test)
	for test in failureList:
		totalTests.append(test)

	testFailure = 0;
	for result in results:
		if(result != 0):
			testFailure = 1;
			message = "test " + str(result) + " failed with message: "
			for test in totalTests:
				if(test.testNum == result):
					message = message + test.message

			print(message + "\n")

	if(not(testFailure)):
		print("All Tests Passed.\n")

	for file in fileList:
		os.remove(file)

if __name__ == "__main__":
	main()
