import os
import subprocess
import filecmp
import sys
import random

# The format strings being fuzzed, how to convert a string into them, and functions to generate a random one.
formatStrings = ["%d", "%lld", "%f", "%x", "%a"]
conversions = ["atoi", "atoll", "atof", "atol", "atof"]
randoms = [lambda: random.randint(-2**31, (2**31)-1), \
           lambda: random.randint(-2**63, (2**63)-1), \
           lambda: random.uniform(-2**63, (2**63)-1), \
           lambda: random.randint(-2**31, (2**31)-1), \
           lambda: random.uniform(-2**63, (2**63)-1)]

# Generates and returns a fuzzed C file
def generateCFile(isMusl):
  cProgram = '#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n'
  if(isMusl):
    cProgram += '#include <stdarg.h>\n#include "musl.h"\n\n#define LEN 10000\nchar buf[LEN];\n'
  cProgram += '\nint main(int argc, char* argv[]) {\n'

  cProgram += fuzz(isMusl)
  
  cProgram += '\treturn 0;\n}'
  return cProgram;

# Generates equivalent C files using standalone musl printf and default printf
def genFiles():
  seed = random.random()
  files = ["musl-printf", "gcc-printf"]
  for f in files:
    random.seed(seed)
    testFile = open('test-printf.c', 'w')
    testFile.write(generateCFile(f == "musl-printf"))
    testFile.close()
    if(len(sys.argv) == 2 and sys.argv[1] == "coverage"):
      os.system("make c-coverage &> /dev/null")
    else:
      os.system("make test-printf &> /dev/null")
    subprocess.call(["mv", "test-printf", f])

# Returns if the musl and default printf outputs are the same
def testEquality():
  musl = subprocess.check_output(["./musl-printf"])
  gcc = subprocess.check_output(["./gcc-printf"])
  return musl == gcc

# Copies the musl standalone printf files to this directory
def copyFiles():
  os.system("cp ../musl-printf-standalone/*.c .")
  os.system("cp ../musl-printf-standalone/*.h .")

# Cleans the directory of the copied and generated files
def clean():
  if(len(sys.argv) != 2 or sys.argv[1] != "coverage"):
    os.system('rm *.c')
    os.system('rm *.h')
  os.remove('musl-printf')
  os.remove('gcc-printf')

# Returns 1000 random printf commands for each format string
def fuzz(isMusl):
  fuzzed = ""
  for i in range(0, len(formatStrings)):
    for count in range(0, 1000):
      testing = randoms[i]()
      if(isMusl):
        fuzzed += '\tmusl_snprintf(buf, LEN, "' + formatStrings[i]  + '\\n", ' + str(testing) + ');\n\tprintf("%s", buf);\n'   
      else:
        fuzzed += '\tprintf("' + formatStrings[i] + '\\n", ' + str(testing) + ');\n'
  return fuzzed

# Entry point for the program
def main():
  copyFiles()
  genFiles()
  if testEquality():
    print("Passed")
    clean()
  else:
    print("One failed")

if __name__ == "__main__":
  main()
