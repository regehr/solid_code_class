import string
import sys
import subprocess
import random
import os
import filecmp
import decimal


def test(value):
	file = open("test-printf.c", "w")
	file.write("#include <stdio.h>\n")
	file.write("#include <stdarg.h>\n")
	file.write("#include \"musl.h\"\n")
	file.write("#define LEN 10000\n")
	file.write("char buf[LEN];\n")
	file.write("int main(int argc, const char *argv[]) {\n")
	file.write("musl_snprintf(buf, LEN, \"%s" "\" , " + str(value) + ");\n")
	file.write("printf(\"%s\", buf);")
	file.write("return 0;\n}")
	file.close()


def main():
	s = " \" Hello fuzzer \\n \" "
	test(s)
	print os.system("gcov vfprintf.c")

if __name__ == "__main__":
	main()
	
	
