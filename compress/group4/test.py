import sys
import subprocess
import os



class oneTest():
	testNum
	fileName
	moq
	programName

	def __init__

def successTest(programName , fileName , testNum , moq):
	try:
		if(moq == 1):
			output = subprocess.check_output([os.getcwd() + "/" + programName , fileName , "0"])
		else:
			output = subprocess.check_output([os.getcwd() + "/" + programName , fileName])

	except subprocess.CalledProcessError, e:
		return testNum

	return 0

def failureTest(programName , fileName , testNum , moq):
	try:
		if(moq == 1):
			output = subprocess.check_output([os.getcwd() + "/" + programName , fileName , "1"])
		else:
			output = subprocess.check_output([os.getcwd() + "/" + programName , fileName])

	except subprocess.CalledProcessError, e:
		return 0

	return testNum

def main():
	moq = 1;
	results = [];
	results.insert(0 , successTest(sys.argv[1] , "someFile.txt" , 1 , moq))
	results.insert(0 , failureTest(sys.argv[1] , "someFile.txt" , 2 , moq))

	for result in results:
		if(result != 0):
			print("test " + str(result) + " failed!")


if __name__ == "__main__":
	main()
