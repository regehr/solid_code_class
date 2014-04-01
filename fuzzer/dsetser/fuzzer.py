import os
import subprocess
import filecmp
import sys
import random

formatStrings = ["%d", "%ll", "%f", "%x", "a"]
conversions = ["atoi", "atoll", "atof", "atol", "atof"]
randoms = [lambda: random.randint(-2**31, (2**31)-1), \
           lambda: random.randint(-2**63, (2**63)-1), \
           lambda: random.uniform(-2**63, (2**63)-1), \
           lambda: random.randint(-2**31, (2**31)-1), \
           lambda: random.uniform(-2**63, (2**63)-1)]

def generateCFile():
  cProgram = '#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n\nint main(int argc, char* argv[]) {\n'
     
  for i in range(0, len(formatStrings)):
    cProgram += '\tif(strcmp(argv[1], "' + formatStrings[i] + '") == 0)\n'
    cProgram += '\t\tprintf(argv[1], ' + conversions[i] + '(argv[2])); \n'
  cProgram += '\treturn 0;\n}'
  return cProgram;

def init():
  testFile = open('test.c', 'w')
  testFile.write(generateCFile())
  testFile.close()
  subprocess.call(["musl-gcc", "-static", "-o", "muslOut", "test.c"])
  subprocess.call(["gcc", "-o", "gccOut", "test.c"])

def testEquality(formatString, input):
  musl = subprocess.check_output(["./muslOut", formatString, input])
  gcc = subprocess.check_output(["./gccOut", formatString, input])
  return musl == gcc

def clean():
  os.remove('test.c')
  os.remove('muslOut')
  os.remove('gccOut')

def fuzz():
  for i in range(0, len(formatStrings)):
    for count in range(0, 1000):
      testing = randoms[i]()
      if(not testEquality(formatStrings[i], str(testing))):
        print(str(testing) + " is Incorrect")

def main():
  init()
  fuzz()
  clean()

if __name__ == "__main__":
  main()
