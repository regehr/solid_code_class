#! /usr/bin/python

import subprocess
import os
import sys


from subprocess import CalledProcessError

def main():
	
	#get the path that contains this file
	myDir = os.getcwd()

	#back up to previous folder
	os.chdir("..")
	
	#get all directories
	folders = os.listdir(".")
	test = folders
	#remove hidden directories
	for dirName in folders:
		for char in dirName:
			if(char == '.'):
				test.remove(dirName)



	for dirName in test:
		#print a header
		print("___________________________________________________________")
		#print the directory name
		print(dirName)
		
		
		currentDir = os.listdir(os.getcwd() +"/" + dirName)
		#is there an executable?
		if "triangle" in currentDir:
			
			#change to this dir
			os.chdir(dirName)
			#get the path ot the binary
			trianglepath = os.getcwd() + "/triangle"
		
			
			
			#copy it into the origional directory
			os.system("cp triangle " + myDir + "/triangle")
			
			#change to the origional directory
			os.chdir(myDir)
			#run the test
			os.system("python testAllHelper.py")
			
		
			#print a footer
			print("___________________________________________________________")
				
			##back up the folder, lather, rinse and repeat
			os.chdir("..")


if __name__ == '__main__':
	main()

