import subprocess

outfile = None

def runTests():
  global outfile
  base = open("base.tri", 'r')
  command = []
  for line in base.readlines():
    if line[0] == '#':
      continue
    if len(command) == 0:
      # Looking for an args line
      parts = line.split()
      if len(parts) == 6:
        command.append(parts)
        command[0] = parts
    elif len(command) == 1:
      # Looking for a results line
      command.append(line)

      # We have two lines now, run the test
      verifyTriangle(command[0], command[1])
      command = []
  if outfile != None:
    outfile.close()
  else:
    print("All tests passed")

def verifyTriangle(args, expected):
  global outfile
  args.insert(0, "./triangle")
  expected = expected.strip()
  try:
    result = subprocess.check_output(args)
  except subprocess.CalledProcessError as e:
    result = e.output
  result = result.decode('utf-8').strip()
  if result != expected:
    if outfile == None:
      print("Failed tests: see testresults.txt for info")
      outfile = open("testresults.txt", 'w')
    print("TEST FAILED:", args, file=outfile)
    print("Output:", result, file=outfile)
    print("Expected:", expected, file=outfile)

import sys
if __name__ == "__main__":
  runTests()
