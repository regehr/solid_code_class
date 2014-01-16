#! /usr/bin/python

import subprocess
import os
import sys
from subprocess import CalledProcessError

def testIso(debug , path):
	toReturn = ""
        output = subprocess.check_output([path , '0' , '0' , '2' , '0', '1' , '4'])
	if(debug == "true"):
		print("output = " + output)
		print("expected = isosceles acute    actual = " + output)
	if(output != "isosceles acute\n"):
		toReturn += "acute "


	output = subprocess.check_output([path , '0' , '0' , '4' , '0', '2' , '1'])
        if(debug == "true"):
                print("output = " + output)
                print("expected = isosceles obtuse    actual = " + output)
        if(output != "isosceles obtuse\n"):
                toReturn += "obtuse "


	output = subprocess.check_output([path , '0' , '0' , '2' , '0', '1' , '1'])
        if(debug == "true"):
                print("output = " + output)
                print("expected = isosceles right    actual = " + output)
        if(output != "isosceles right\n"):
                toReturn += "right "


	output = subprocess.check_output([path , '0' , '0' , '2' , '0', '1' , '2147483647'])
        if(debug == "true"):
                print("output = " + output)
                print("expected = isosceles acute    actual = " + output)
        if(output != "isosceles acute\n"):
                toReturn += "acuteEdgeCase "

	output = subprocess.check_output([path , '0' , '0' , '0' , '2147483646' , '64', '1073741823'])
        if(debug == "true"):
                print("output = " + output)
                print("expected = isosceles obtuse    actual = " + output)
        if(output != "isosceles obtuse\n"):
                toReturn += "obtuseEdgeCase "

	

	return toReturn

def testSca(debug , path):
        toReturn = ""
        output = subprocess.check_output([path , '0' , '0' , '2' , '3', '3' , '1'])
        if(debug == "true"):
                print("output = " + output)
                print("expected = scalene acute    actual = " + output)
        if(output != "scalene acute\n"):
                toReturn += "acute "


        output = subprocess.check_output([path , '0' , '0' , '4' , '4', '2' , '4'])
        if(debug == "true"):
                print("output = " + output)
                print("expected = scalene obtuse    actual = " + output)
        if(output != "scalene obtuse\n"):
                toReturn += "obtuse "


        output = subprocess.check_output([path , '0' , '0' , '2' , '0', '0' , '4'])
        if(debug == "true"):
                print("output = " + output)
                print("expected = scalene right    actual = " + output)
        if(output != "scalene right\n"):
                toReturn += "right "

        return toReturn

def testNot(debug , path):
        toReturn = ""
        output = subprocess.check_output([path , '0' , '0' , '1' , '1', '2' , '2'])
        if(debug == "true"):
                print("output = " + output)
                print("expected = not a triangle    actual = " + output)
        if(output != "not a triangle\n"):
                toReturn += "line "


        output = subprocess.check_output([path , '0' , '0' , '0' , '0', '0' , '0'])
        if(debug == "true"):
                print("output = " + output)
                print("expected = not a triangle    actual = " + output)
        if(output != "not a triangle\n"):
                toReturn += "equal "

        return toReturn



def main():
	debug = "false"
	#returnedValue = testIso(debug)
	#if(returnedValue != ""):
	#	print("failed isosceles: " + returnedValue)

	#returnedValue = testSca(debug)
        #if(returnedValue != ""):
        #        print("failed scalene: " + returnedValue)
	
	#returnedValue = testNot(debug)
        #if(returnedValue != ""):
        #        print("failed not a triangle: " + returnedValue)



	test = os.listdir("../")
	iter = test
	for dirName in iter:
		for char in dirName:
			if(char == '.'):
				test.remove(dirName)
	
	finalResults = ""
	for dirName in test:
		curDir = os.listdir("../" + dirName)
		if "triangle.c" in curDir:
			os.chdir("../" + dirName)
			output = os.system("make")
			print(output)
			path = "./triangle"
			try:
				toReturn = ""

				results = testIso(debug , path)# + testSca(debug , path) + testNot(debug , path)
				if(results == ""):
					toReturn += "(passed isosceles) "
				else:
					toReturn += "failed isoceles(" + results + ") "

				results = testSca(debug , path)
				if(results == ""):
					toReturn += "(passed scalene) "
				else:
					toReturn += "failed scalene(" + results +") "

				results = testNot(debug , path)
				if(results == ""):
					toReturn += "(passed Not a Triangle)"
				else:
					toReturn += "failed NotaTriangle(" + results + ") "

				results = toReturn
			except CalledProcessError as e:
				results = dirName + " returned the error code: " + str(e.returncode)
			finalResults += dirName + ": " + results + "\n"
			os.system("make clean")
	
	print(finalResults)
			


if __name__ == '__main__':
	main()

