import os
import subprocess
import filecmp
import sys
import string
import random

# The format strings being fuzzed and functions to generate a random one.
formatStrings = ["d", "i", "u", "lld", "f", "F", "o", "x", "X", "a", "A", "e", "E", "g", "G", "s", "c"]
randoms = [lambda: random.randint(-2147483647, 2147483647), \
           lambda: random.randint(-2147483647, 2147483647), \
           lambda: random.randint(0, 2147483647), \
           lambda: random.randint(-9223372036854775807, 9223372036854775807), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: random.randint(-32767, 32767), \
           lambda: random.randint(-32767, 32767), \
           lambda: random.randint(-32767, 32767), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: random.uniform(-9223372036854775807, 9223372036854775807), \
           lambda: '"' + randomString() + '"', \
           lambda: "'" + str(random.choice(string.ascii_letters)) + "'"]

# Generates a random string that has no % in it
def randomString():
  randString = ""
  for i in range(0, random.randint(0, 20)):
    choice = str(random.choice(string.ascii_letters))
    if choice != "%":
      randString += choice
  return randString

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

# Returns a random prefix
def prefix(formatString):
  prefixesAllowed = ["d", "i", "o", "x", "X", "a", "A", "f", "F"]
  prefix = ""
  rand = random.randint(0, 10)
  if(rand < 5 or formatString not in prefixesAllowed):
    return ""
  # Flag
  rand = random.randint(0, 10)
  if rand == 1:
    prefix += "-"
  if rand == 2:
    prefix += "+"
  if rand == 3:
    prefix += " "
  if rand == 4:
    prefix += "0"
  # Width
  rand = random.randint(0, 5)
  if rand == 1:
    prefix += str(random.randint(1, 20))
  # Precision
  rand = random.randint(0, 5)
  if rand == 1:
    prefix += str(random.randint(1, 20))
  return prefix

# Returns a random suffix
def suffix(formatString):
  return ""

# Returns a random format string and list of parameters
def formatAndArgs():
  index = random.randint(0, len(formatStrings)-1)
  formatString = "%" + formatStrings[index]
  args = str(randoms[index]())
  for i in range(0, random.randint(1, 15)):
    padding = randomString()
    index = random.randint(0, len(formatStrings)-1)
    formatString += padding + "%" + prefix(formatStrings[index]) + formatStrings[index] + suffix(formatStrings[index])
    args += ", " + str(randoms[index]())
  return {'format':formatString, 'args':args}

# Returns 1000 random printf commands
def fuzz(isMusl):
  fuzzed = ""
  for count in range(0, 1000):
    fAndA = formatAndArgs()
    formatString = fAndA.get('format')
    args = fAndA.get('args')
    if(isMusl):
      fuzzed += '\tmusl_snprintf(buf, LEN, "' + formatString  + '\\n", ' + args + ');\n\tprintf("%s", buf);\n'   
    else:
      fuzzed += '\tprintf("' + formatString + '\\n", ' + args + ');\n'
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
