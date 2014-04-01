import random
import subprocess
import string	

def fuzzInts():
	f = open("test_printf.c", "w")
	f.write("#include <stdio.h>\n")
	f.write("#include \"musl.h\"\n")
	f.write("#define LEN 10000\n")
	f.write("int main() {\r")
	f.write("char buf[LEN];\n")
	
	for i in range(1, 10000):
		d = random.randint(1,10000)
		f.write("\tmusl_snprintf (buf, LEN, \"%d"  "\", " + str(d) + ");\n")
	
	f.write("return 0;\r}")
	f.close

#def fuzzChars():
#	f = open("test_printf.c", "w")
#	f.write("#include <stdio.h>\n")
#	f.write("#include \"musl.h\"\n")
#	f.write("int main() {\r")
	
#	for i in range(1, 10000):
#		char = random.choice(string.ascii_lowercase)
#		f.write("musl_snprintf (\"%c"  "\", " + char + ");\n")f
	
#	f.write("return 0;\r}")
#	f.close

def main():
	fuzzInts()
	#fuzzChars()

main()
