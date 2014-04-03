import subprocess
import sys
import random
import os
import string
import filecmp
import decimal
from random import randrange


#I tried over and over to break all the fuzzing cases 
#into smaller chunks but my code coverage was dimishing
# as i added more and more cases. This is the only thing
#i could get to truly work. I find this interesting
#and i will definately continue to work on fuzzing.

def large_string(n):
    ret = ""
    for i in xrange(n):
        ret += random.choice(string.letters)
    return ret

def random_int(n):
    return random.getrandbits(n)

def fuzz_all():
    typ = "c %03d %c %.3f %6.3f %e %5.3s %.d %+i %#x %u %o %g %% %a %-l % ll %p %ls %+ld %lu %5lf %-lg %le %h %#010X %z %i %i %l %ll %llu %hu %c %i %i %c %s"
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
    dH = hex(random_int(8))
    h = 3
    lg = 3.141592
    maximum = 2**32 - 1
    minimum = -2**32 - 1
    l = -12
    uc = 65+4
    m = " 'c ' + 65 "
    s2 = "  \" Hello World \\n \" "

    file = open("test-printf.c", "w")
    file.write("#include <stdio.h>\n")
    file.write("#include <stdarg.h>\n")
    file.write("#include <math.h>\n")
    file.write("#include \"musl.h\"\n")
    file.write("#define LEN 10000\n")
    file.write("char buf[LEN];\n")
    file.write("int main(int argc, const char *argv[]) {\n")
    file.write("musl_snprintf(buf, LEN, \"%" + typ +  "\" , " + str(c) + "," + str(d) + "," + str(i) + "," +str(f) + "," +str(f) + "," +str(e) + "," +str(s) + "," +str(d) +  "," +str(i) +  "," + str(x) +  "," + str(i)+  "," +str(o) + "," +str(d) +"," +str(sym) +  "," + str(dH) +  "," + str(d) +  "," + str(d) +  "," + str(d) +  "," + str(h) +  "," + str(d) +  "," + str(d) +  "," + str(f) +  "," + str(lg) +  "," + str(e) +  "," + str(h) +  "," + str(x) + "," + str(i) +  "," + str(i)  + "," + str(i) +  "," + str(l) +  "," + str(l)  +  "," + str(d) +  "," + str(d)+  "," + str(uc)+  "," + str(maximum)+  "," + str(minimum)+ "," + str(m)+  "," + str(s2) +");\n")
    file.write("printf(\"%s\", buf);")
    file.write("return 0;\n}")
    file.close()


def main():

    fuzz_all()

    print os.system("gcov vfprintf.c")

if __name__ == "__main__":
    main()
