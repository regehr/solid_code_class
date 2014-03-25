import string
import sys
import subprocess
import random
import os


def small_fuzz():
	f = open("hello.c", "rb+")
	offset = random.randrange(0, 0x7ffff)
	f.seek(offset, 0)
	f.write("%c%c%c" % (small_fuzz(), small_fuzz(), small_fuzz()))
	f.close()





def main():
	small_fuzz()
	return 0

if __name__ == "__main__":
	main()
