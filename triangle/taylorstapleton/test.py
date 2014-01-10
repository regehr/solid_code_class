#! /usr/bin/python

import subprocess

def testIso(debug):
	toReturn = ""
        output = subprocess.check_output(['./triangle' , '0' , '0' , '2' , '0', '1' , '4'])
	if(debug == "true"):
		print("output = " + output)
		print("expected = isosceles acute    actual = " + output)
	if(output != "isosceles acute\n"):
		toReturn += "acute "


	output = subprocess.check_output(['./triangle' , '0' , '0' , '4' , '0', '2' , '1'])
        if(debug == "true"):
                print("output = " + output)
                print("expected = isosceles obtuse    actual = " + output)
        if(output != "isosceles obtuse\n"):
                toReturn += "obtuse "


	output = subprocess.check_output(['./triangle' , '0' , '0' , '2' , '0', '1' , '1'])
        if(debug == "true"):
                print("output = " + output)
                print("expected = isosceles right    actual = " + output)
        if(output != "isosceles right\n"):
                toReturn += "right "

	return toReturn

def testSca(debug):
        toReturn = ""
        output = subprocess.check_output(['./triangle' , '0' , '0' , '2' , '3', '3' , '1'])
        if(debug == "true"):
                print("output = " + output)
                print("expected = scalene acute    actual = " + output)
        if(output != "scalene acute\n"):
                toReturn += "acute "


        output = subprocess.check_output(['./triangle' , '0' , '0' , '4' , '4', '2' , '4'])
        if(debug == "true"):
                print("output = " + output)
                print("expected = scalene obtuse    actual = " + output)
        if(output != "scalene obtuse\n"):
                toReturn += "obtuse "


        output = subprocess.check_output(['./triangle' , '0' , '0' , '2' , '0', '0' , '4'])
        if(debug == "true"):
                print("output = " + output)
                print("expected = scalene right    actual = " + output)
        if(output != "scalene right\n"):
                toReturn += "right "

        return toReturn


def main():
	debug = "false"
	returnedValue = testIso(debug)
	if(returnedValue != ""):
		print("failed isosceles " + returnedValue)

	returnedValue = testSca(debug)
        if(returnedValue != ""):
                print("failed scalene " + returnedValue)



if __name__ == '__main__':
	main()

