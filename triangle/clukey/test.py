#!/usr/bin/env python2.7
#
# Triangle Analyzer tests
#
# Student: John Clukey
# Date: January 13, 2014

import subprocess


if __name__ == "__main__":
    
    passed = 0
    failed = 0            
    fd = open("../clukey/tests.txt", "r")

    expected = fd.readline()
    while expected != "":
        pts = fd.readline().split()
        result = subprocess.check_output(["./triangle",
                                          pts[0],
                                          pts[1],
                                          pts[2],
                                          pts[3],
                                          pts[4],
                                          pts[5]])
        if expected == result:
            passed += 1
        else:
            failed += 1
            print("=== Failed test ===")
            print("Input: (" + pts[0] + ", " + pts[1] + ") " 
                  + "(" + pts[2] + ", " + pts[3] + ") "
                  + "(" + pts[4] + ", " + pts[5] + ")")
            print("Expected: " + expected.strip())
            print("Actual: " + result.strip() + "\n")
        expected = fd.readline()
        
    print "Passed: " + str(passed) + " Failed: " + str(failed)
