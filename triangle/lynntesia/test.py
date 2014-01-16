#!/usr/bin/env python27
# python script for more robust testing
import sys
print sys.path
import subprocess

#python27 test.py

print '**Starting tests**\n'

def isNotATriangle():
     output = subprocess.check_output(['./triangle', '0', '0', '0', '0', '0', '0'])
     if not "not a triangle" in output:
             return "not a triangle TEST FAILED"
     output = subprocess.check_output(['./triangle', '0', '0', '0', '0', '1', '2'])
     if not "not a triangle" in output:
             return "not a triangle TEST FAILED"

     return "not a triangle TEST PASSED"
    

#def isScalene():

#def isIsosceles():

#def isAcute():

def isObtuse():
        output = subprocess.check_output(['./triangle', '-5', '0', '3', '3', '0', '2'])
        if not "obtuse" in output:
                return "obtuse TEST FAILED"
        output = subprocess.check_output(['./triangle', '3', '0', '3', '3', '0', '2'])
        if not "obtuse" in output:
                return "obtuse TEST FAILED"
        output = subprocess.check_output(['./triangle', '3', '0', '3', '3', '2', '2'])
        if not "obtuse" in output:
                return "obtuse TEST FAILED"
        output = subprocess.check_output(['./triangle', '4', '5', '3', '11', '8', '12'])
        if not "obtuse" in output:
                return "obtuse TEST FAILED"

        return "obtuse TEST PASSED"


def isRight():
        output = subprocess.check_output(['./triangle', '3', '3', '3', '7', '9', '3'])
        if not "right" in output:
                return "right TEST FAILED"
        output = subprocess.check_output(['./triangle', '-5', '1', '5', '1', '0', '6'])
        if not "right" in output:
                return "right TEST FAILED"
        if not "right" in output:
                return "right TEST FAILED"

        return "right TEST PASSED"

def main():
     print("*Not a triangle test: " + isNotATriangle() + " * \n")
     #print("*Scalene test: " + isScalene())
     #print("*Isosceles test: " + isIsosceles())
     #print("*Acute test: " + isAcute())
     print("*Obtust test: " + isObtuse())
     print("*Right test: " + isRight())



if __name__ == '__main__':
     main()
