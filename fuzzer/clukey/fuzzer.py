#!/usr/local/bin/python3
#
# Fuzzer for musl vfprintf
#
# Student: John Clukey

import subprocess
import random
import string

chars = string.ascii_letters + string.digits

def rand_chars():
    return ''.join(random.choice(chars) for _ in range(randint(0, 20)))


def write_header(fd):
    fd.write("#include <stdio.h>\n")
    fd.write("#ifdef MUSL\n#include \"musl.h\"\n")
    fd.write("#define snprintf musl_snprintf\n#endif\n")
    fd.write("#define LEN 10000\nchar buf[LEN];\nint main(){\n")


def write_footer(fd):
    fd.write("return 0;}")


def run_test(fname):
    normlresult = subprocess.check_output(["make",
                                           "gcc"])
    normlresult = subprocess.check_output(["./test-printf"])
    muslresult = subprocess.check_output(["make",
                                          "musl"])
    muslresult = subprocess.check_output(["./test-printf"])
    if muslresult != normlresult:
        subprocess.call(["mv", fname, "./fuzzfails/"+fname+str(test)])
        subprocess.call(["rm", "test-printf"])
        print("Failed test " + str(test))
        test += 1
    else:
        subprocess.call(["rm", "test-printf"])
        #subprocess.call(["rm", fname])


def rand_int():
    args = ','
    flags = ['', '', '', '-', '+', ' ', '0']
    widths = ['', '', '', str(random.randint(0, 10)), '*']
    precisions = ['', '', '', '.' + str(random.randint(0, 10)), '.*']
    flag = flags[random.randint(0, len(flags)-1)]
    width = widths[random.randint(0, len(widths)-1)]
    precision = precisions[random.randint(0, len(precisions)-1)]
    if width == '*':
        args += str(random.randint(0, 10))
        args += ','
    if precision == '.*':
        args += str(random.randint(0, 10))
        args += ','
    args += str(random.randint(-(2**31), 2**31-1))
    return ['%' + flag + width + precision + 'd', args]
    


def main():
    random.seed()
    test = 0
    fname = "test-printf.c"

    fd = open(fname, "w");
    write_header(fd)
    for i in range(1000):
        x = rand_int()
        fd.write("snprintf(buf, LEN, \"" + x[0] + "\" " + x[1] + ");")
        fd.write("printf(buf);\n")
    write_footer(fd)
    fd.close()

    run_test(fname)


if __name__ == "__main__":
    main()
  
