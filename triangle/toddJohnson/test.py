#!/usr/bin/env python27

import subprocess

#Test if inputs do not create a triangle
def testIsTriangle():
    #Same point
    output = subprocess.check_output(['./triangle', '0', '0', '0', '0', '0', '0'])
    if not "not" in output:
        return "fail"
    #Co-linear
    output = subprocess.check_output(['./triangle', '0', '0', '1', '1', '2', '2'])
    if not "not" in output:
        return "fail"
    #Co-linear
    output = subprocess.check_output(['./triangle', '0', '0', '0', '1', '0', '2'])
    if not "not" in output:
        return "fail"
    
    return "Passed"

#Test for right angle
def testIsRight():
    output = subprocess.check_output(['./triangle', '0', '0', '1', '0', '1', '1'])
    if not "right" in output:
        return "fail"
    
    output = subprocess.check_output(['./triangle', '0', '0', '1', '0', '1', '2147483647'])
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
    if not "isosceles" in output:
        return "fail"
    
    output = subprocess.check_output(['./triangle', '0', '0', '2', '1', '0', '2'])
    if not "isosceles" in output:
        return "fail"

    output = subprocess.check_output(['./triangle', '0', '0', '2', '1', '4', '0'])
    if not "isosceles" in output:
        return "fail"

    return "Passed"

#Test for no equal sides, "Scalene"
def testIsScalene():
    output = subprocess.check_output(['./triangle', '0', '0', '0', '2', '1', '0'])
    if not "scalene" in output:
        return "fail"

    output = subprocess.check_output(['./triangle', '0', '0', '2', '2', '0', '3'])
    if not "scalene" in output:
        return "fail"

    output = subprocess.check_output(['./triangle', '0', '0', '1', '1', '0', '3'])
    if not "scalene" in output:
        return "fail"

    return "Passed"
#Added tests
def newTests():
#Obtuse Scalene
    output = subprocess.check_output(['./triangle', '0', '0', '1', '2', '0', '1'])
    if not "obtuse" in output:
        return "Test1: Should be scalene obtuse"
    
    output = subprocess.check_output(['./triangle', '0', '0', '3', '4', '1', '2'])
    if not "obtuse" in output:
        return "Test2: Should be scalene obtuse"

    output = subprocess.check_output(['./triangle', '0', '0', '3', '4', '1', '4'])
    if not "scalene obtuse" in output:
        return "Test3: Should be scalene obtuse"


#Right Scalene
    output = subprocess.check_output(['./triangle', '0', '0', '3', '4', '0', '4'])
    if not "scalene right" in output:
        return "Test4: Should be scalene right"
        
    output = subprocess.check_output(['./triangle', '0', '0', '3', '4', '0', '4'])
    if not "scalene right" in output:
        return "Test5: Should be scalene right"
#Acute Scalene
    output = subprocess.check_output(['./triangle', '0', '0', '1', '3', '5', '1'])
    if not "scalene acute" in output:
        return "Test6: Should be scalene acute "
    
#Isosceles Right
    output = subprocess.check_output(['./triangle', '0', '0', '0', '1', '1', '0'])
    if not "isosceles right" in output:
        return "Test7: Should be ososceles right"
    
    output = subprocess.check_output(['./triangle', '4', '4', '6', '2', '2', '2'])
    if not "isosceles right" in output:
        return "Test8: Should be ososceles right"
#Isosceles Acute
    output = subprocess.check_output(['./triangle', '2', '0', '3', '4', '1', '4'])
    if not "isosceles acute" in output:
        return "Test9: Should be ososceles acute"
    
    output = subprocess.check_output(['./triangle', '0', '0', '2', '0', '1', '2'])
    if not "isosceles acute" in output:
        return "Test10: Should be ososceles acute"

#Isosceles Obtuse
    output = subprocess.check_output(['./triangle', '4', '4', '7', '2', '1', '2'])
    if not "isosceles obtuse" in output:
        return "Should be ososceles obtuse"

    return "Passed"
  
def main():
    print("Triangle Test: " + testIsTriangle())
    print("Right Angle Test: " + testIsRight())
    print("Obtuse Angle Test: " + testIsObtuse())
    print("Acute Angle Test: " + testIsAcute())
    print("Isosceles Test: " + testIsIso())
    print("Scalene Test: " + testIsScalene())
    print("New added tests: " + newTests())
    

if __name__ == '__main__':
    main()
            
    
    
