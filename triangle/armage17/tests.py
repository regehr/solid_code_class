#!/usr/bin/env python27

import subprocess

EXE = './triangle'

def notATriangle():
    #Same point
    out = subprocess.check_output([EXE, '0', '0', '0', '0', '1', '1'])
    if "not a triangle\n" != out:
        print("failed 1, out= {}".format(out)),

    #Vertical line
    out = subprocess.check_output([EXE, '0', '0', '0', '1', '0', '2'])
    if "not a triangle\n" != out:
        print("failed 2, out= {}".format(out)),

    #Horizontal line
    out = subprocess.check_output([EXE, '0', '0', '1', '0', '2', '0'])
    if "not a triangle\n" != out:
        print("failed 3, out= {}".format(out)),

    #Diagonal line, all points on line
    out = subprocess.check_output([EXE, '0', '0', '1', '1', '2', '2'])
    if "not a triangle\n" != out:
        print("failed 4, out= {}".format(out)),

    print("notATriangle() is done.")

def rightTriangle():
    #iso right
    out = subprocess.check_output([EXE, '0', '0', '1', '1', '1', '0'])
    if "isosceles right\n" != out:
        print("failed 1, out= {}".format(out)),

    #scal right
    out = subprocess.check_output([EXE, '0', '0', '1', '3', '1', '0'])
    if "scalene right\n" != out:
        print("failed 2, out= {}".format(out)),

    #iso right, using int max
    out = subprocess.check_output([EXE, '0', '0', '2147483647', '2147483647', '2147483647', '0'])
    if "isosceles right\n" != out:
        print("failed 3, out= {}".format(out)),

    #scalene right, int max, bit different than above
    out = subprocess.check_output([EXE, '0', '0', '1', '2147483647', '1 ', '0'])
    if "scalene right\n" != out:
        print("failed 4, out= {}".format(out)),

    print("rightTriangle() is done.")

def acuteTriangle():
    #iso
    out = subprocess.check_output([EXE, '0', '0', '2', '0', '1', '4'])
    if "isosceles acute\n" != out:
        print("failed 1, out= {}".format(out)),

    print("acuteTriange() is done.")

def main():
    print("Not a triangle tests:")
    notATriangle()
    print("Right Triangle tests:")
    rightTriangle()
    print("Acute Triangle tests:")
    acuteTriangle()

if __name__ == '__main__':
    main()
