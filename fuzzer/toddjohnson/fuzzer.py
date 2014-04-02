import subprocess
import sys
import random
import os
import string
import filecmp
import decimal
from random import randrange

def large_string(n):
    ret = ""
    for i in xrange(n):
        ret += random.choice(string.letters)
    return ret

def random_int(n):
    return random.getrandbits(n)

def fuzz1():
    typ = "c %d %f %e %s %d %i %x %u %o %g %% %a %l %ll %p"
    c = "'" + random.choice(string.letters) + "'"
    d = random_int(8)
    f = random.uniform(1.0, 1000.1)
    e = 12345678.
    s = '"'+large_string(10)+'"'
    d = random_int(4)
    i = 14
    x = hex(random_int(16))
    o = oct(random_int(32))
    sym = "'%'"
    dH = hex(12)

    file = open("test-printf.c", "w")
    file.write("#include <stdio.h>\n")
    file.write("#include <stdarg.h>\n")
    file.write("#include <math.h>\n")
    file.write("#include \"musl.h\"\n")
    file.write("#define LEN 10000\n")
    file.write("char buf[LEN];\n")
    file.write("int main(int argc, const char *argv[]) {\n")
    file.write("musl_snprintf(buf, LEN, \"%" +  typ +  "\" , " + str(c) + "," + str(d) + "," +str(f) + "," +str(e) + "," +str(s) + "," +str(d) +  "," +str(i) +  "," + str(x) +  "," + str(i)+  "," +str(o) + "," +str(d) +"," +str(sym) +  "," + str(dH) +  "," + str(d) +  "," + str(d) +  "," + str(d) + ");\n")
    file.write("printf(\"%s\", buf);")
    file.write("return 0;\n}")
    file.close()


def main():

    fuzz1()

    print os.system("gcov vfprintf.c")

if __name__ == "__main__":
    main()
