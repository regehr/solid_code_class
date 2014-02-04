# python3 ftw
# TODO: more helpful error messages
import os
import subprocess

def die(message):
  raise SystemExit(message)

def codesfrom(filename):
  output = subprocess.check_output(["./huff", "-t", filename])
  output = output.decode('utf-8')
  return [ x.strip() for x in output.split('\n') if len(x) > 0 ]

def generalcheck(output, filename):
  """Checks to make sure no encoding is the prefix of another, and other universal properties."""
  if len(output) != 256:
    print("Error in {0}: not 256 output codes".format(filename))
    return False

  modify = sorted(output, key=len)
  for i,code1 in enumerate(modify):
    for code2 in modify[(i+1):]:
      if code2.startswith(code1):
        print("Error in {0}: {1} is the prefix of {2}, both codes".format(filename, code1, code2))
        return False
  # TODO: verify that the only tree leaves are the chars
  # I was going to add another test here, but I forgot what it was... I'll probably remember sometime
  return True

def oneeachtest():
  assert os.path.exists("./1each.bin")
  output = codesfrom("1each.bin")
  if not generalcheck(output, "1each.bin"):
    return

  # In this case, the output should be the ascii representation of binary integers in order
  for i,line in enumerate(output):
    intrep = int(line.strip(), 2)
    if i != intrep:
      print("Error in 1each.bin output: line {0} is incorrect".format(i+1))
      break
  else:
    print("1each.bin test passed")

def increasingtest():
  assert os.path.exists("./increasing.bin")
  output = codesfrom("increasing.bin")
  if not generalcheck(output, "increasing.bin"):
    return

  # In this case, the length of lines should be decreasing, because character frequency increases with ascii code
  lastintrep = None
  lastlinelen = None
  for (i,line) in enumerate(output):
    intrep = int(line.strip(), 2)
    linelen = len(line.strip())
    if lastintrep != None:
      # Check against last line
      if linelen > lastlinelen:
        print("Error in increasing.bin output: line {0} is longer than previous line".format(i+1))
        break
      elif linelen == lastlinelen and intrep < lastintrep:
        print("Error in increasing.bin output: line {0} appears further to left in tree than previous line".format(i+1))
        break
    lastintrep = intrep
    lastlinelen = linelen
  else:
    print("increasing.bin test passed")

def emptytest():
  assert os.path.exists("./empty.bin")
  output = codesfrom("empty.bin")
  if not generalcheck(output, "empty.bin"):
    return

  # In this case, the output should be the ascii representation of binary integers in order
  # In this case, the output should be:
  # 0 repeated (255 - i) times followed by a 1, if the char has a non-zero code
  # 0 repeated 255 times, if the char is zero
  def expectedforascii(i):
    if i == 0:
      return '0' * 255
    else:
      return ('0'*(255-i)) + '1'

  for i,line in enumerate(output):
    if line != expectedforascii(i):
      print("Error in empty.bin output: line {0} is incorrect".format(i+1))
      print(line)
      print(expectedforascii(i))
      break
  else:
    print("empty.bin test passed")

if __name__ == "__main__":
  oneeachtest()
  increasingtest()
  emptytest()
