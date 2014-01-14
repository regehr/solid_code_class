#!/usr/bin/env python27

import subprocess

#Test if inputs do not create a triangle
def testIsTriangle():
    #Same point
    output = subprocess.check_output(['./triangle', '0', '0', '0', '0', '0', '0'])
    if not "not" in output:
        return "fail"
    #Co-linear
    subprocess.check_output(['./triangle', '0', '0', '1', '1', '2', '2'])
    if not "not" in output:
        return "fail"
    #Bad input
    subprocess.check_output(['./triangle', '0', '0', '1'])
    if not "not" in output:
        return "fail"

    return "Passed"

#Test for right angle
def testIsRight():
    output = subprocess.check_output(['./triangle', '0', '0', '1', '0', '1', '1'])
    if not "right" in output:
        return "fail"

    subprocess.check_output(['./triangle', '0', '0', '1', '0', '1', '2147483647'])
    if not "right" in output:
        return "fail"

    return "Passed"

#Test for acute angle
def testIsAcute():
    output = subprocess.check_output(['./triangle', '0', '0', '2', '2', '0', '3'])
    if not "acute" in output:
        return "fail"

    return "Passed"

def testIsObtuse():
    output = subprocess.check_output(['./triangle', '5', '5', '10', '5', '3', '10' ])
    if not "obtuse" in output:
        return "fail"

    return "Passed"

#Test for 2 equal sides, "Isosceles"
def testIsIso():
    output = subprocess.check_output(['./triangle', '0', '0', '0', '1', '1', '0'])
    if not "isosceles " in output:
        return "fail"

    output = subprocess.check_output(['./triangle', '0', '0', '2', '1', '0', '2'])
    if not "isosceles " in output:
        return "fail"

    output = subprocess.check_output(['./triangle', '0', '0', '2', '1', '4', '0'])
    if not "isosceles " in output:
        return "fail"

    return "Passed"

#Test for no equal sides, "Scalene"
def testIsScalene():
    output = subprocess.check_output(['./triangle', '0', '0', '0', '2', '1', '0'])
    if not "scalene " in output:
        return "fail"

    output = subprocess.check_output(['./triangle', '0', '0', '2', '2', '0', '3'])
    if not "scalene " in output:
        return "fail"

    output = subprocess.check_output(['./triangle', '0', '0', '1', '1', '0', '3'])
    if not "scalene " in output:
        return "fail"

    return "Passed"
  
def main():
    print("Triangle Test: " + testIsTriangle())
    print("Right Angle Test: " + testIsRight())
    print("Obtuse Angle Test: " + testIsObtuse())
    print("Acute Angle Test: " + testIsAcute())
    print("Isosceles Test: " + testIsIso())
    print("Scalene Test: " + testIsScalene())


if __name__ == '__main__':
    main()
            
    
    
