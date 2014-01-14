#!/usr/bin/env python27

import subprocess

EXE = './triangle'

def notATriangle():
    #Same point
    out = subprocess.check_output([EXE, '0', '0', '0', '0', '1', '1'])
    if not "not" in out:
        return "failed"

    #Vertical line
    out = subprocess.check_output([EXE, '0', '0', '0', '1', '0', '2'])
    if not "not" in out:
        return "failed"

    #Horizontal line
    out = subprocess.check_output([EXE, '0', '0', '1', '0', '2', '0'])
    if not "not" in out:
        return "failed"

    #Diagonal line, all points on line
    out = subprocess.check_output([EXE, '0', '0', '1', '1', '2', '2'])
    if not "not" in out:
        return "failed"

    return "good"

def rightTriangle():
    #iso right
    out = subprocess.check_output([EXE, '0', '0', '1', '1', '1', '0'])
    if not "right" in out:
        return "failed"
    if not "isosceles" in out:
        return "failed"

    #scal right
    out = subprocess.check_output([EXE, '0', '0', '1', '3', '1', '0'])
    if not "right" in out:
        return "failed"
    if not "scalene" in out:
        return "failed"

    return "good"

def main():
    print("Not a triangle tests: " + notATriangle())
    print("Right Triangle tests: " + rightTriangle())

if __name__ == '__main__':
    main()
