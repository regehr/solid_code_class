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


def string_fuzz():
	f = open("strings.c", "w")
	f.write("#include <stdio.h>\r\n")
	f.write("int main(int argc, const char *argv[]) {\r\n")
	f.write("printf('string test');\n")
	
	n = 100000
	test_words = large_string(n)
	f.write("printf(\"%s\\n\", " + test_words + ");\n")
	# close file
	f.write("}\r\n")
	call("strings.c", "strings")
	p = subprocess.Popen("./strings", shell=True, stdout=subprocess.PIPE)
	out, err = p.communicate()
	listOut = filter(None, out.split('\n'))
	os.remove("string.c")
	
def large_string(n):
	ret = ""
	for i in xrange(n):
		ret += random.choice(string.letters)
	return ret

def rand_int_fuzz():
	f = open("randints.c", "w")
	f.write("#include <stdio.h>\r\n")
	f.write("int main(int argc, const char *argv[]) {\r\n")
	f.write("printf('integer test');\n")
	n = 10240
	test_ints = random_bigints(n)
	f.write("printf(\"%d\\n\", " + str(test_ints) + ");\n")
	f.write("}\r\n")
	call("randints.c", "randints")
	p = subprocess.Popen("./randints", shell=True, stdout=subprocess.PIPE)
	out, err = p.communicate()
	listOut = filter(None, out.split('\n'))
	os.remove("randints.c")
	
def random_bigints(n):
	return random.getrandbits(n)

def write_headers(f):
	f.write("#include <stdio.h>\r\n")
	f.write("int main(int argc, const char *argv[] {\r\n")
	f.write("printf(stringtest\n);\n")
	return f

def call(filename, name):
	subprocess.call(["/usr/local/musl/bin/musl-gcc", "-static", filename, "-w", "-o", name])
	

def main():
	#string_fuzz()
	rand_int_fuzz()
	return 0

if __name__ == "__main__":
	main()
