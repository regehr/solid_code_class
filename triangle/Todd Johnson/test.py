#!/usr/bin/env python27
#
#
#

import subprocess

def testIsTriangle():
    toReturn = ""
    #test co-linear
    output = subprocess.check_output(['./triangle', '0', '0', '0', '1', '0', '5'])
    if not "not" in output:
        toReturn = "expected = not a triangle actual = " + output
        return toReturn;
    #Use same point
    subprocess.check_output(['./triangle', '0', '0', '0', '0', '1', '2147483647'])
    if not "not" in output:
        toReturn = "expected = not a triangle actual = " + output
        return toReturn;

    return toReturn

def testIsRight():
    toReturn = ""
    #small triangle test
    output = subprocess.check_output(['./triangle', '0', '0', '1', '0', '1', '1'])
    if not "right" in output:
        toReturn = "expected = right actual = " + output
        return toReturn;
    #skinniest tall right triangle
    subprocess.check_output(['./triangle', '0', '0', '1', '0', '1', '2147483647'])
    if not "right" in output:
        toReturn = "expected = right actual = " + output
        return toReturn;

    return toReturn


def testIsAcute():
    toReturn = ""
   
    output = subprocess.check_output(['./triangle', '0', '0', '2', '2', '0', '3'])
    if not "acute" in output:
        toReturn = "expected = acute actual = " + output
        return toReturn;

    return toReturn

def testIsObtuse():

    toReturn = ""

    output = subprocess.check_output(['./triangle', '5', '5', '10', '5', '3', '10' ])
    if not "obtuse" in output:
        toReturn = "expected = obtuse actual = " + output
        return toReturn;

    return toReturn

def testIsIsoScalene():
    toReturn = ""
    
    output = subprocess.check_output(['./triangle', '0', '0', '1', '0', '1', '1'])
    if not "isosceles " in output:
        toReturn = "expected = right actual = " + output
        return toReturn;
    
    subprocess.check_output(['./triangle', '0', '0', '1', '0', '1', '2147483647'])
    if not "right" in output:
        toReturn = "expected = right actual = " + output
        return toReturn;

    return toReturn



def main():
    value = testIsTriangle()
    if(value != ""):
        print("failed isTriangle: " + value)
        return

    value = testIsRight()
    if(value != ""):
        print("failed isRight: " + value)
        return
    
    value = testIsObtuse()
    if(value != ""):
        print("failed isObtuse: " + value)
        return

    value = testIsAcute()
    if(value != ""):
        print("failed isAcuteObtuse: " + value)
        return

    value = testIsIsoScalene()
    if(value != ""):
        print("failed isIsoScalene: " + value)
        return

    print("All tests pass")

if __name__ == '__main__':
    main()
            
    
    
