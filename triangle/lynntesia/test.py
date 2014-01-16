#!/usr/bin/env python27
# python script for more robust testing
import sys
import subprocess 

#python27 test.py
# got some test cases from Todd Johnson

print '**Starting tests**\n'

def isNotATriangle():
     output = subprocess.check_output(['./triangle', '0', '0', '0', '0', '0', '0'])
     if not "not a triangle" in output:
             return "not a triangle TEST FAILED"
     output = subprocess.check_output(['./triangle', '0', '0', '0', '0', '1', '2'])
     if not "not a triangle" in output:
             return "not a triangle TEST FAILED"

     return "not a triangle TEST PASSED"
    

def isScalene():
     output = subprocess.check_output(['./triangle', '0', '0', '0', '2', '1', '0'])
     if not "scalene" in output:
          return "scalene TEST FAILED"
     output = subprocess.check_output(['./triangle', '0', '0', '2', '2', '1', '0'])
     if not "scalene" in output:
          return "scalene TEST FAILED"
     output = subprocess.check_output(['./triangle', '0', '0', '1', '1', '0', '3'])
     if not "scalene" in output:
          return "scalene TEST FAILED"

     return "scalene TEST PASSED"

def isIsosceles():
     output = subprocess.check_output(['./triangle', '1', '3', '2', '0', '-1', '-1'])
     if not "isosceles" in output:
          return "isosceles TEST FAILED"     
     output = subprocess.check_output(['./triangle', '1', '2', '4', '-1', '6', '4'])
     if not "isosceles" in output:
          return "isosceles TEST FAILED"

     return "isosceles TEST PASSED"

# got one acute test case from Todd Johnson
def isAcute():
     output = subprocess.check_output(['./triangle', '4', '5', '3', '11', '8', '12'])
     if not "acute" in output:
          return "acute TEST FAILED"
     output = subprocess.check_output(['./triangle', '0', '0', '2', '2', '0', '3'])
     if not "acute" in output:
          return "acute TEST FAILED"
     output = subprocess.check_output(['./triangle', '6', '8', '6', '-12', '1', '7'])
     if not "acute" in output:
          return "acute TEST FAILED"

     return "acute TEST PASSED"

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

     return "right TEST PASSED"

def main():
     print("*Not a triangle test: " + isNotATriangle() + " * \n")
     print("*Scalene test: " + isScalene())
     print("*Isosceles test: " + isIsosceles())
     print("*Acute test: " + isAcute() + " * \n")
     print("*Obtust test: " + isObtuse() + " * \n")
     print("*Right test: " + isRight() + " * \n")
     print '**End tests**\n\n'



if __name__ == '__main__':
     main()
