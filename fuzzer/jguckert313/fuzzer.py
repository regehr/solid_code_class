import random
import subprocess
import string	

# used to fuzz %d, %o, %x, %X, %f, %e, %E
def fuzz_nums():
	f = open("test_printf.c", "a")
	for i in range(1, 1000):
		n = str(random.randint(1,10000))
		f.write("\tmusl_snprintf (buf, LEN, \"%d"  "\", " + n + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%o"  "\", " + n + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%x"  "\", " + n + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%X"  "\", " + n + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%#o"  "\", " + n + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%#x"  "\", " + n + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%#X"  "\", " + n + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%e"  "\", " + n + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%E"  "\", " + n + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%f"  "\", " + n + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%l"  "\", " + n + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%ll"  "\", " + n + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%h"  "\", " + n + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%hh"  "\", " + n + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%L"  "\", " + n +"L" +");\n")


	f.close()

# used to fuzz %c, %s
def fuzz_chars():
	f = open("test_printf.c", "a")
	s = ""
	for i in range(1, 1000):
		c = random.choice(string.lowercase)
		s += c
		f.write("\tmusl_snprintf (buf, LEN, \"%c"  "\", " + "\"" + c + "\"" + ");\n")
		f.write("\tmusl_snprintf (buf, LEN, \"%s"  "\", " + "\"" + s + "\"" + ");\n")


def main():
	f = open("test_printf.c", "w")
	f.write("#include <stdio.h>\n")
	f.write("#include <stdarg.h>\n")
	f.write("#include \"musl.h\"\n")
	f.write("\n#define LEN 1000\n")
	f.write("char buf[LEN];\n")
	f.write("\nint main() {\r")
	f.close()
	fuzz_nums()
	fuzz_chars()
	f = open("test_printf.c", "a")
	f.write("\n\treturn 0;\n")
	f.write("}")

main()
#ulong, ullong, short, ushort