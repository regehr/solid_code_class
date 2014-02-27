# python3 ftw
# TODO: more helpful error messages
import os
import subprocess

def die(message):
  raise SystemExit(message)

def codesfrom(filename):
  output = subprocess.check_output(["./rhuff", "-t", filename])
  output = output.decode('utf-8')
  return [ x.strip() for x in output.split('\n') if len(x) > 0 ]

class Leaf(object):
  def __init__(self, char):
    self.char = char
    self.left = None
    self.right = None

# Left = 0 bit, Right = 1 bit
class Node(object):
  def __init__(self, left, right):
    self.left = left
    self.right = right
    self.char = -1

def buildWithBit(tree, bit):
  assert bit == "0" or bit == "1", "bad bit"

  if bit == "0":
    if tree.left == None:
      tree.left = Node(None, None)
    return tree.left
  else:
    if tree.right == None:
      tree.right = Node(None, None)
    return tree.right

def buildTree(output):
  root = Node(None, None)

  for i,code in enumerate(output):
    leaf = Leaf(i)
    cur = root
    for bit in code[:-1]:
      cur = buildWithBit(cur, bit)
    if code[-1] == "0":
      cur.left = leaf
    else:
      cur.right = leaf

  return root

def checkTree(tree):
  if tree.left == None and tree.right == None:
    # Make sure the only leaves are the ones that hold chars
    return tree.char >= 0
  elif tree.left != None and tree.right != None:
    # If it's an internal node, check both children
    return checkTree(tree.left) and checkTree(tree.right)
  else:
    # No nodes with only one child
    return False

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

  tree = buildTree(output)
  if not checkTree(tree):
    print("Error in {0}: not all tree leaves are chars".format(filename))
    return False

  # I was going to add another test here, but I forgot what it was... I'll probably remember sometime

  return True

def roundtrip(filename):
  """Compress + decompress and make sure it's the same"""
  ret = subprocess.call(["./rhuff", "-c", filename])
  if ret != 0:
    print("Error compressing {0}".format(filename))
    return False

  os.rename("{0}.rhuff".format(filename), "{0}.2.rhuff".format(filename))
  ret = subprocess.call(["./rhuff", "-d", "{0}.2.rhuff".format(filename)])
  if ret != 0:
    print("Error decompressing {0}.2.rhuff".format(filename))
    os.remove("{0}.2.rhuff".format(filename))
    return False

  ret = subprocess.call(["diff", filename, "{0}.2".format(filename)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  os.remove("{0}.2.rhuff".format(filename))
  os.remove("{0}.2".format(filename))
  if ret != 0:
    print("Round-trip on {0} gave different file".format(filename))
    return False

  return True

def compressCheck(filename):
  """Compress and compare to existing correct compressed version"""
  ret = subprocess.call(["./rhuff", "-c", filename])
  if ret != 0:
    print("Error compressing {0}".format(filename))
    return False

  ret = subprocess.call(["diff", "{0}.rhuff".format(filename), "{0}.ex.rhuff".format(filename)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  os.remove("{0}.rhuff".format(filename))
  if ret != 0:
    print("Compressed version of {0} was not correct".format(filename))
    return False

  return True

def oneeachtest():
  assert os.path.exists("./1each.bin")
  total = 4
  output = codesfrom("1each.bin")
  if not generalcheck(output, "1each.bin"):
    return 0, total

  # In this case, the output should be the ascii representation of binary integers in order
  for i,line in enumerate(output):
    intrep = int(line.strip(), 2)
    if i != intrep:
      print("Error in 1each.bin output: line {0} is incorrect".format(i+1))
      break
  else:
    if not roundtrip("1each.bin"):
      return 2, total
    if not compressCheck("1each.bin"):
      return 3, total
    return 4, total

  return 1, total

def increasingtest():
  assert os.path.exists("./increasing.bin")
  total = 3
  output = codesfrom("increasing.bin")
  if not generalcheck(output, "increasing.bin"):
    return 0, total

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
    if not roundtrip("increasing.bin"):
      return 2, total
    return 3, total
  return 1, total

def emptytest():
  assert os.path.exists("./empty.bin")
  total = 4
  output = codesfrom("empty.bin")
  if not generalcheck(output, "empty.bin"):
    return 0, total

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
    if not roundtrip("empty.bin"):
      return 2, total
    if not compressCheck("empty.bin"):
      return 3, total
    return 4, total

  return 1, total

def rand1test():
  assert os.path.exists("./rand1")
  total = 2
  output = codesfrom("rand1")
  if not generalcheck(output, "rand1"):
    return 0, total
  if not roundtrip("rand1"):
    return 1, total
  return 2, total

def rand2test():
  assert os.path.exists("./rand2")
  total = 2
  output = codesfrom("rand2")
  if not generalcheck(output, "rand2"):
    return 0, total
  if not roundtrip("rand2"):
    return 1, total
  return 2, total

def rand3test():
  assert os.path.exists("./rand3")
  total = 2
  output = codesfrom("rand3")
  if not generalcheck(output, "rand3"):
    return 0, total
  if not roundtrip("rand3"):
    return 1, total
  return 2, total

if __name__ == "__main__":
  tests = [oneeachtest, increasingtest, emptytest, rand1test, rand2test, rand3test]
  passed = 0
  total = 0
  for test in tests:
    p, t = test()
    passed += p
    total += t

  print("{0}/{1} tests passed".format(passed, total))
