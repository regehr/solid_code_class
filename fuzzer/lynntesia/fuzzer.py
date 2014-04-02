import string
import sys
import subprocess
import random
import os
import filecmp
import decimal
from random import randrange

# worked with Todd Johnson on tests & makefile
# code coverage = 53.13%

def fuzz_it(value):
	file = open("test-printf.c", "w")
	file.write("#include <stdio.h>\n")
	file.write("#include <stdarg.h>\n")
	file.write("#include <math.h>\n")
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

def sm_int_fuzz():
	n = 31
	test_ints = random_int(n)
	return test_ints
	

def random_int(n):
	return random.getrandbits(n)

def large_int_fuzz():
	n = 100
	test_ints = random_int(n)
	return test_ints

def char_fuzz():
	for i in range(255):
		intstr = str(randrange(255))
		fuzz_it_type(intstr, "c")
	for i in range(255):
		intstr2 = str(randrange(-128, 127))
		fuzz_it_type(intstr2, "c")
	a = format(random.getrandbits(8), '08b')
	num = int(a, 2)
	fuzz_it_type(num, "c")

def u_short_int():
	for i in range(200):
		ui = str(randrange(0, 65535))
		fuzz_it_type(ui, "u")
	
def short_int():
	for i in range(200):
		ssi = str(randrange(-32768, 32767))
		fuzz_it_type(ssi, "i")

# short int, unsigned short int, unsigned int
def bit_16():
	a = format(random.getrandbits(16), '016b')
	num = int(a, 2)
	fuzz_it_type(num, "d")
	fuzz_it_type(num, "u")
	fuzz_it_type(num, "x")

# long int, int, float
def bit_32():
	a = format(random.getrandbits(32), '032b')
	num = int(a, 2)
	fuzz_it_type(num, "f")

# double
def bit_64():
	a = format(random.getrandbits(64), '064b')
	num = int(a, 2)
	fuzz_it_type(num, "lf")
	fuzz_it_type(num, "lg")
	fuzz_it_type(num, "le")

# long double
def bit_96():
	a = format(random.getrandbits(96), '096b')
	num = int(a, 2)
	fuzz_it_type(num, "ld")

# strings 2048 bytes (?)
def byte_2048():
	st = "".join([random.choice(string.ascii_lowercase)
        for x in xrange(2048)])
	st = " \" " + st + " \\n \" "
	fuzz_it(st)		

def many_fuzz():
	typ = "c %d %f %e %s %d %u %o %x %g %llu %hu %hhx %lc %+d %.0f %#.0f %.9g %ls %10d %02d %a %1$s"
	c = "'" + random.choice(string.letters) + "'"
	d = random_int(8)
	f = random.uniform(1.0, 1000.1)
	e = 12345678.
	s = '"'+large_string(10)+'"'
	d = random_int(4)
	i = random_int(16)
	u = random_int(32)
	o = random_int(31)
	x = str(random_int(31))
	g = random.uniform(1.0, 1000.1)
	llu = str(randrange(0, 4294967296))
	hex_range = ['a', 'b', 'c', 'd', 'e', 'f']
	hu = 0x1ffffff	
	hhx = 0xFFFFFFF
	lc = "'" + random.choice(string.ascii_lowercase) + "'"
	plusd = randrange(0, 31)
	dotf = random.uniform(0.1, 10.0)
	hashdotf = random.uniform(0.1, 50.0)
	dotg = random.uniform(0.1, 10.0)
	ls = '"'+large_string(10)+'"'
	dspace = -123546789000
	dfill = 123456789000
	a = random_int(2)
	s_dolla = '"'+ "weekday" + '"'

	file = open("test-printf.c", "w")
	file.write("#include <stdio.h>\n")
	file.write("#include <stdarg.h>\n")
	file.write("#include \"musl.h\"\n")
	file.write("#define LEN 10000\n")
	file.write("char buf[LEN];\n")
	file.write("int main(int argc, const char *argv[]) {\n")
	file.write("musl_snprintf(buf, LEN, \"%" +  typ +  "\" , " + 
		str(c) + "," + str(d) + "," +str(f) + "," +str(e) + "," +str(s) + "," +
		str(d) + str(i) + "," + str(u) + "," +str(o) + "," +str(x) + "," + str(g) + "," +
		str(llu) + "," + str(hu) + "," + str(hhx) + "," + str(lc) + "," + 
		str(plusd) + "," + str(dotf) + "," + str(hashdotf) + "," + str(dotg) + "," + 
		str(ls) + "," + str(dspace) + "," + str(dfill) + "," + str(a) + "," + 
		str(s_dolla) + ");\n")
	file.write("printf(\"%s\", buf);")
	file.write("return 0;\n}")
	file.close()


	

def main():
	'''
	 d /* int, signed base 10 */
	 i /* int, signed base 10 */
	 o /* int, unsigned base 8, no leading 0 */
	 x /* int, unsigned base 16, abcdef with no leading 0x */
	 X /* int, unsigned base 16, ABCDEF with no leading 0X */
	 u /* int, unsigned base 10 */
	 s /* char *, nul terminated sequence of characters */
	 c /* int, single character */
	 f /* double, notation [-]mm.dd */
	 e /* double, notation [-]m.dde[+/-]xx */
	 E /* double, notation [-]m.ddE[+/-]xx */
	 g /* double, %e if exponent is less than -4 or >= the precision, %f otherwise */
	 G /* double, %E if exponent is less than -4 or >= the precision, %f otherwise */
	'''
	char_fuzz()
	u_short_int()
	short_int()
	hello_test = " \" Hello fuzzer \\n \" "
	fuzz_it(hello_test)
	string_test = string_fuzz()
	fuzz_it(string_test)
	int_test = int_fuzz()
	fuzz_it_type(int_test, "i")
	uint_test = sm_int_fuzz()
	fuzz_it_type(uint_test, "lu")
	bit_16()
	bit_32()
	bit_64()
	many_fuzz()

	
	
		
	
	
	print os.system("gcov vfprintf.c")

if __name__ == "__main__":
	main()
	
	

