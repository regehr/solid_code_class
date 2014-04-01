import subprocess
import sys
import random
import os
import string
import filecmp
import decimal
from random import randrange

#Collaborated with Lynn Gao

#Helo World Test 
#Ensures code coverage is working
def helloTest(value):
    file = open('test-printf.c', 'w')
    file.write("#include <stdio.h>\n")
    file.write("#include <stdarg.h>\n")
    file.write("#include \"musl.h\"\n")
    file.write("#define LEN 10000\n")
    file.write("char buf[LEN];\n")
    file.write("int main(void){\n")
    file.write("musl_snprintf (buf, LEN, \"%s"  "\" , " + str(value) + ");\n");
    file.write("printf(\"%s\", buf);")
    file.write("return 0;\n}")
    file.close()

#Fuzz Test 
def fuzz(value, typeof):
    file = open("test-printf.c", "w")
    file.write("#include <stdio.h>\n")
    file.write("#include <stdarg.h>\n")
    file.write("#include \"musl.h\"\n")
    file.write("#define LEN 10000\n")
    file.write("char buf[LEN];\n")
    file.write("int main(int argc, const char *argv[]) {\n")
    file.write("musl_snprintf(buf, LEN, \"%" + typeof + "\" , " + str(value) + ");\n")
    file.write("printf(\"%s\", buf);")
    file.write("return 0;\n}")
    file.close()

#Fuzz Test adding options -, +, " ", #
def fuzz_options(value, typeof, option):
    file = open("test-printf.c", "w")
    file.write("#include <stdio.h>\n")
    file.write("#include <stdarg.h>\n")
    file.write("#include \"musl.h\"\n")
    file.write("#define LEN 10000\n")
    file.write("char buf[LEN];\n")
    file.write("int main(int argc, const char *argv[]) {\n")
    file.write("musl_snprintf(buf, LEN, \"%" + option + typeof + "\" , " + str(value) + ");\n")
    file.write("printf(\"%s\", buf);")
    file.write("return 0;\n}")
    file.close()

#Test as many types (i.e. %d, %s, %i, etc.) as can think of

#Int Test
def intTest():
    fuzz(-2147483648, "i")
    fuzz_options(-2147483648, "i", "-")
    fuzz_options(-2147483648, "i", "+")
    fuzz_options(-2147483648, "i", "\" \" ")
    fuzz_options(-2147483648, "i", "#")

def uintTest():
    fuzz(4294967295, "u")
    fuzz(4294967295, "o")
    fuzz_options(4294967295, "o", "#")
    fuzz_options(4294967295, "u", "-")
    fuzz_options(4294967295, "u", "+")
    fuzz_options(4294967295, "u", " ")
    fuzz_options(4294967295, "u", "#")

#Hext Test
def hexTest():
    fuzz(-2147483648, "x")
    fuzz(4294967295, "x")
    fuzz(4294967295, "X")
    fuzz_options(4294967295, "x", "#")

#Long Test
def longTest():
    fuzz(-1024, "l")
    fuzz(1024, "ul")

#Long Long
def longlongTest():
    fuzz(-2147483647L, "lli")
    fuzz(4294967295L, "llu")
    fuzz(-2147483647L, "llx")
    fuzz(4294967295L, "llx")

def longdoubleTest():
    fuzz(1e37, "Lf")
    fuzz(1e37, "llf")
    fuzz(1e-37, "llf")
    fuzz(1e+37, "lle")
    fuzz(1e-37, "lle")

#Char Test
def charTest(value):
    fuzz(value, "c")
    fuzz(value, "u")

#Double Test
def doubleTest():
    fuzz(12.22, "d")
    fuzz(12.22, "E")
    fuzz(12.22, "g")

#Float Test
def floatTest():
    fuzz(1.34, "f")
    fuzz(1.34, "F")
    fuzz(1.34, "G")

#Short Test
def ushortTest():
    fuzz(65535, "hu")
    fuzz(65535, "hx")

def shortTest():
    fuzz(-32768 , "hi")
    fuzz(-32768, "hx")


#Fuzz randomness
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
        value  = str(randrange(255))
        fuzz(value, "c")
    for i in range(255):
        value2 = str(randrange(-128, 127))
        fuzz(value2, "c")
    a = format(random.getrandbits(8), '08b')
    num = int(a, 2)
    fuzz(num, "c")

def u_short_int():
    for i in range(200):
        ui = str(randrange(0, 65535))
        fuzz(ui, "u")

def short_int():
    for i in range(200):
        ssi = str(randrange(-32768, 32767))
        fuzz(ssi, "i")

# short int, unsigned short int, unsigned int
def bit_16():
    a = format(random.getrandbits(16), '016b')
    num = int(a, 2)
    fuzz_options(num, "d", "-")
    fuzz_options(num, "u", "+")
    fuzz_options(num, "x", "#")


# long int, int, float
def bit_32():
    a = format(random.getrandbits(32), '032b')
    num = int(a, 2)
    fuzz(num, "f")

# double
def bit_64():
    a = format(random.getrandbits(64), '064b')
    num = int(a, 2)
    fuzz(num, "lf")
    fuzz(num, "lg")
    fuzz(num, "le")

def main():

    s = "  \" Hello World \\n \" "
    helloTest(s)     #21.80% coverage
    intTest()        #23.71%
    uintTest()
    hexTest()
    longTest()
    longlongTest()
    longdoubleTest()
    s = " ' d ' "
    charTest(s)
    doubleTest()
    floatTest()
    ushortTest()
    shortTest()
    char_fuzz()    
    u_short_int()    
    short_int()
    int_test = int_fuzz()
    fuzz(int_test, "i")   
    uint_test = sm_int_fuzz()
    fuzz(uint_test, "lu") 
    bit_16()
    bit_32()
    bit_64() #40.87% (Gotten 42.51%)

    print os.system("gcov vfprintf.c")

if __name__ == "__main__":
    main()

#flags -> -, +, #, 0
