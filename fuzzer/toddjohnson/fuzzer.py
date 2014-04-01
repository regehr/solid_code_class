import subprocess
import sys
import random
import os
import string
import filecmp
import decimal

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


if __name__ == "__main__":
    s = "  \" Hello World \\n \" "
    helloTest(s)

    print os.system("gcov vfprintf.c")
    

