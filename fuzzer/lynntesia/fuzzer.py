import string
import sys
import subprocess
import random
import os
import filecmp
import decimal


def fuzz_it(value):
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

def fuzz_it_type(value, typeof):
	file = open("test-printf.c", "w")
	file.write("#include <stdio.h>\n")
	file.write("#include <stdarg.h>\n")
	file.write("#include \"musl.h\"\n")
	file.write("#define LEN 10000\n")
	file.write("char buf[LEN];\n")
	file.write("int main(int argc, const char *argv[]) {\n")
	file.write("musl_snprintf(buf, LEN, \"%" +  typeof +  "\" , " + str(value) + ");\n")
	file.write("printf(\"%s\", buf);")
	file.write("return 0;\n}")
	file.close()

def string_fuzz():
	n = 100000
	test_words = large_string(n)
	ret =  " \""+ test_words+ " \\n \" "
	return ret

def large_string(n):
	ret = ""
	for i in xrange(n):
		ret += random.choice(string.letters)
	return ret

def int_fuzz():
	n = 63
	test_ints = random_int(n)
	return test_ints

def bigint_fuzz():
	n = 31
	test_ints = random_int(n)
	return test_ints
	

def random_int(n):
	return random.getrandbits(n)


def main():
	hello_test = " \" Hello fuzzer \\n \" "
	fuzz_it(hello_test)
	string_test = string_fuzz()
	fuzz_it(string_test)
	int_test = int_fuzz()
	fuzz_it_type(int_test, "i")
	uint_test = bigint_fuzz()
	fuzz_it_type(uint_test, "lu")
	
	
	print os.system("gcov vfprintf.c")

if __name__ == "__main__":
	main()
	
	
