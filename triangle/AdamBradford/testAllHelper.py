#! /usr/bin/python
#! /usr/local/bin/python

#test basis borrowed from Tyler Stapleton

import subprocess
import inspect


def testIsIsoScalene():
        toReturn = ""
        ###These tests should  produce an iso triangle
        output = subprocess.check_output(['./triangle' , '0' , '0' , '2' , '0', '1' , '1'])
        if not "isosceles" in output:
		   # print("expected = isosceles    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "
        output = subprocess.check_output(['./triangle' , '0' , '0' , '2' , '0', '1' , '2147483647'])
        if not "isosceles" in output:
		   #print("expected = isosceles    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        #widest iso triangle 
        output = subprocess.check_output(['./triangle' , '0' , '0' , '2147483646' , '0', '1073741823' , '1'])
        if not "isosceles" in output:
		   #print("expected = isosceles    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "
        #same as previous triangle but make it the max height
        output = subprocess.check_output(['./triangle' , '0' , '0' , '2147483646' , '0', '1073741823' , '2147483647'])
        if not "isosceles" in output:
		   #print("expected = isosceles    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "
        #now bring in the two sides
        output = subprocess.check_output(['./triangle' , '1073741822' , '0' , '1073741824' , '0', '1073741823' , '2147483647'])
        if not "isosceles" in output:
		   #print("expected = isosceles    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        #take the above three triangles and make them off by 1
        output = subprocess.check_output(['./triangle' , '0' , '0' , '2147483646' , '0', '1073741822' , '1'])
        if not "scalene" in output:
		   #print("expected = scalene    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "
        #same as previous triangle but make it the max height
        output = subprocess.check_output(['./triangle' , '0' , '0' , '2147483646' , '0', '1073741822' , '2147483647'])
        if not "scalene" in output:
		   #print("expected = scalene    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "
        #now bring in the two sides
        output = subprocess.check_output(['./triangle' , '1073741822' , '0' , '1073741824' , '0', '1073741824' , '2147483647'])
        if not "scalene" in output:
		   #print("expected = scalene    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "
        

        return toReturn

def testIsAcuteObtuse():
        
        toReturn = ""

        ###These tests should  produce an acute triangle
        output = subprocess.check_output(['./triangle' , '0' , '0' , '3' , '0', '1' , '7'])
        if not "acute" in output:
		   #print("expected = acute    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        #skinniest tall right triangle 
        output = subprocess.check_output(['./triangle' , '0' , '0' , '3' , '0', '2' , '2147483647'])
        if not "acute" in output:
		   #print("expected = acute    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        #skinniest wide right triangle 
        output = subprocess.check_output(['./triangle' , '0' , '0' , '0' , '2', '2147483647' , '1'])
        if not "acute" in output:
		   #print("expected = acute    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        ###These tests should  produce an obtuse triangle
        output = subprocess.check_output(['./triangle' , '0' , '0' , '3' , '0', '1' , '1'])
        if not "obtuse" in output:
		   #print("expected = obtuse    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        #skinniest tall right triangle 
        output = subprocess.check_output(['./triangle' , '0' , '0' , '3' , '0', '4' , '2147483647'])
        if not "obtuse" in output:
		   #print("expected = obtuse    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        #skinniest wide right triangle 
        output = subprocess.check_output(['./triangle' , '0' , '0' , '0' , '2', '2147483647' , '3'])
        if not "obtuse" in output:
		   #print("expected = obtuse    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "
        

        return toReturn

def testIsRight():
        #small right triangle
        toReturn = ""
        output = subprocess.check_output(['./triangle' , '0' , '0' , '1' , '0', '1' , '1'])
        if not "right" in output:
		   #print("expected = right    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        #skinniest tall right triangle 
        output = subprocess.check_output(['./triangle' , '0' , '0' , '1' , '0', '1' , '2147483647'])
        if not "right" in output:
		   #print("expected = right    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        #skinniest wide right triangle 
        output = subprocess.check_output(['./triangle' , '0' , '0' , '0' , '1', '2147483647' , '0'])
        if not "right" in output:
		   #print("expected = right    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "



        ###These tests should not produce a right triangle, same tests as above but off by one
        output = subprocess.check_output(['./triangle' , '0' , '0' , '1' , '0', '2' , '1'])
        if "right" in output:
		   #print("expected = right    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        #skinniest tall right triangle 
        output = subprocess.check_output(['./triangle' , '0' , '0' , '1' , '0', '2' , '2147483647'])
        if "right" in output:
		   #print("expected = right    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        #skinniest wide right triangle 
        output = subprocess.check_output(['./triangle' , '0' , '0' , '0' , '1', '2147483647' , '2'])
        if "right" in output:
		   #print("expected = right    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "
        

        return toReturn

def testIsTriangle():
        toReturn = ""

        #two points the same
        output = subprocess.check_output(['./triangle' , '0' , '0' , '0' , '0', '0' , '2'])
        if(output != "not a triangle\n"):
		   #print("expected = not a triangle    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        #small line
        output = subprocess.check_output(['./triangle' , '0' , '0' , '0' , '1', '0' , '2'])
        if(output != "not a triangle\n"):
		   #print("expected = not a triangle    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        #huge line
        output = subprocess.check_output(['./triangle' , '0' , '0' , '0' , '1', '0' , '2147483647'])
        if(output != "not a triangle\n"):
		   #print("expected = not a triangle    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        #huge line with point in the center
        output = subprocess.check_output(['./triangle' , '0' , '0' , '0' , '1147483647', '0' , '2147483647'])
        if(output != "not a triangle\n"):
		   #print("expected = not a triangle    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        #small line on a slope        1/100
        output = subprocess.check_output(['./triangle' , '1' , '1' , '2' , '101', '3' , '201'])
        if(output != "not a triangle\n"):
		   #print("expected = not a triangle    actual = " + output + " : Line %d" % lineno())
                toReturn += "line "

        



        return toReturn


def main():
	finalOutput = ""
	returnedValue = testIsTriangle()
	if(returnedValue != ""):
		finalOutput += "failed isTriangle"
  

	returnedValue = testIsRight()
	if(returnedValue != ""):
		finalOutput += "failed isTriangle"

	returnedValue = testIsAcuteObtuse()
	if(returnedValue != ""):
		finalOutput += "failed isTriangle"

	returnedValue = testIsIsoScalene()
	if(returnedValue != ""):
		finalOutput += "failed isTriangle"

	if(finalOutput != ""):
		print("Failed")
	else:
		print("Passed")


def lineno():
    """Returns the current line number in our program."""
    return inspect.currentframe().f_back.f_lineno


if __name__ == '__main__':
	main()

