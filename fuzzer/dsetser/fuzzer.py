import os
import subprocess
import filecmp
import sys
import random

def init():
  testFile = open('test.c', 'w')
  testFile.write('#include <stdio.h>\nint main(int argc, char* argv[]) { printf(argv[1], atoi(argv[2])); }')
  testFile.close()
  subprocess.call(["musl-gcc", "-static", "-o", "muslOut", "test.c"])
  subprocess.call(["gcc", "-o", "gccOut", "test.c"])

def testEquality(formatString, input):
  subprocess.call(["./muslOut", formatString, input], stdout=open("musl.txt", "w"))
  subprocess.call(["./gccOut", formatString, input], stdout=open("gcc.txt", "w"))
  return filecmp.cmp("musl.txt", "gcc.txt")

def clean():
  os.remove('test.c')
  os.remove('muslOut')
  os.remove('gccOut')
  os.remove('musl.txt')
  os.remove('gcc.txt')

def fuzz():
  for i in range(0, 1000):
    testing = random.randint((-2**32)-1, 2**32)
    if(not testEquality("%d", str(testing))):
      print(str(testing) + " is Incorrect")

def main():
  init()
  fuzz()
  clean()

if __name__ == "__main__":
  main()
