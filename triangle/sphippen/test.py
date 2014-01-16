import subprocess

# This remains unopened unless a test failure occurs.
# In that case, it is opened and remains open until after all tests are run.
outfile = None

def runTests():
  '''Loads base tests and checks the triangle program on each test case.'''
  global outfile
  base = open("base.tri", 'r')
  command = []
  for line in base.readlines():
    if line[0] == '#':
      # Skip comment lines
      continue

    if len(command) == 0:
      # Looking for an args line
      parts = line.split()

      # 3 xs, 3 ys = 6 total args
      if len(parts) == 6:
        command.append(parts)

    elif len(command) == 1:
      # Looking for a results line
      command.append(line)

      # We have both needed lines now, run the test
      verifyTriangle(command[0], command[1])
      command = []
  if outfile != None:
    outfile.close()
  else:
    print("All tests passed")

def verifyTriangle(args, expected):
  '''Run the triangle program with the given args and verify that it gives the expected output.'''
  global outfile

  args.insert(0, "./triangle")

  # Run the triangle program and grab the output
  try:
    result = subprocess.check_output(args)
  except subprocess.CalledProcessError as e:
    result = e.output

  result = result.decode('utf-8').strip()
  expected = expected.strip()

  if result != expected:
    # Open the error output file if it doesn't exist yet
    if outfile == None:
      print("Failed tests: see testresults.txt for info")
      outfile = open("testresults.txt", 'w')

    print("TEST FAILED:", args, file=outfile)
    print("Output:", result, file=outfile)
    print("Expected:", expected, file=outfile)

import sys
if __name__ == "__main__":
  runTests()
