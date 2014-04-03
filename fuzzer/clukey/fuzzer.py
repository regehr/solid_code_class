#!/usr/local/bin/python3
#
# Fuzzer for musl vfprintf
#
# Student: John Clukey

import subprocess
import random
import string

def pointer():
    fmt = '%p'
    args = ',' + "&n"
    return [fmt, args]

def rand_float():
    args = ','
    flags = ['', '', '', '-', ' ', '#', '0']
    widths = ['', '', '', str(random.randint(0, 10)), '*']
    precisions = ['', '', '', '.' + str(random.randint(0, 10)), '.*']
    lengths = ['', '', '', 'L']
    flag = flags[random.randint(0, len(flags)-1)]
    width = widths[random.randint(0, len(widths)-1)]
    precision = precisions[random.randint(0, len(precisions)-1)]
    length = lengths[random.randint(0, len(lengths)-1)]
    argchoices = [str(random.uniform(-1651561561561561561, 1561689461651561562)),
                  str(random.uniform(-1651561561561561561, 1561689461651561562)),
                  str(random.random()),
                  str(random.random()),
                  str(0),
                  'INFINITY',
                  'NAN']
                  
    if width == '*':
        args += str(random.randint(0, 10))
        args += ','
    if precision == '.*':
        args += str(random.randint(0, 10))
        args += ','
    args += argchoices[random.randint(0, len(argchoices)-1)]
    specifiers = ['f', 'F', 'e', 'E','g','G','a','A']
    return ['%' + flag + width + precision + length + specifiers[random.randint(0,len(specifiers)-1)], args]

def rand_n():
    fmt = "%n"
    args = ',' + "&n"
    return [fmt, args]

def rand_chars():
    chars = string.ascii_letters + string.digits
    charlist = list(chars)
    charlist.append('%%')
    return [''.join(random.choice(charlist) for _ in range(random.randint(0, 5))), '']

def rand_char():
    fmt = "%c"
    arg = "," + str(random.randint(0, 255))
    return [fmt, arg]

def write_header(fd):
    fd.write("#include <stdio.h>\n")
    fd.write("#include <stdint.h>\n")
    fd.write("#include <math.h>\n")
    fd.write("#ifdef MUSL\n#include \"musl.h\"\n")
    fd.write("#define snprintf musl_snprintf\n#endif\n")
    fd.write("#define LEN 10000\nchar buf[LEN];\nint main(){\n")
    fd.write("int n;\n")


def write_footer(fd):
    fd.write("return 0;}")


def run_test(fname, test):
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
    else:
        subprocess.call(["rm", "test-printf"])
        #subprocess.call(["rm", fname])

def rand_string():
    args = ','
    flags = ['-', ' ']
    flag = flags[random.randint(0, len(flags)-1)]
    widths = ['', '', '', str(random.randint(0, 21)), '*']
    width = widths[random.randint(0, len(widths)-1)]
    precisions = ['', '', '', '.' + str(random.randint(0, 21)), '.*']
    precision = precisions[random.randint(0, len(precisions)-1)]
    if width == '*':
        args += str(random.randint(0, 6))
        args +=','
    if precision == '.*':
        args += str(random.randint(0, 6))
        args += ','
    args += "\""
    args += rand_chars()[0]
    args += "\""
    return ['%' + flag + width + precision + 's', args]

def rand_int():
    args = ','
    flags = ['', '', '', '-', '+', ' ', '0']
    widths = ['', '', '', str(random.randint(0, 10)), '*']
    precisions = ['', '', '', '.' + str(random.randint(0, 10)), '.*']
    lengths = ['', '', '', 'hh', 'h', 'l', 'll', 'j', 'z', 't']
    length = lengths[random.randint(0, len(lengths)-1)]
    argschoice = {'' : str(random.randint(-(2**31), 2**31 - 1)),
                  'hh' : str(random.randint(-(2**7), 2**7 - 1)),
                  'h' : str(random.randint(-(2**15), 2**15 - 1)),
                  'l' : str(random.randint(-(2**31), 2**31 - 1)),
                  'll' : str(random.randint(-(2**63), 2**63 - 1)),
                  'j' : '(intmax_t)' + str(random.randint(-(2**63), 2**63 - 1)),
                  'z' : '(size_t)' + str(random.randint(-(2**31), 2**31 - 1)),
                  't' : str(random.randint(-(2**31), 2**31 - 1))}
    flag = flags[random.randint(0, len(flags)-1)]
    width = widths[random.randint(0, len(widths)-1)]
    precision = precisions[random.randint(0, len(precisions)-1)]
    if width == '*':
        args += str(random.randint(0, 10))
        args += ','
    if precision == '.*':
        args += str(random.randint(0, 10))
        args += ','
    
    args += argschoice[length]
    return ['%' + flag + width + precision + length + ['d','i'][random.randint(0,1)], args]

def rand_unsigned():
    utypes = ['u', 'o', 'x', 'X']
    utype = utypes[random.randint(0, 3)]
    args = ','
    flags = ['', '', '', '-', ' ', '#', '0']
    widths = ['', '', '', str(random.randint(0, 10)), '*']
    if utype == 'u':
        flags = ['', '', '', '-', ' ', '0']
    precisions = ['', '', '', '.' + str(random.randint(0, 10)), '.*']
    flag = flags[random.randint(0, len(flags)-1)]
    width = widths[random.randint(0, len(widths)-1)]
    precision = precisions[random.randint(0, len(precisions)-1)]
    lengths = ['', '', '', 'hh', 'h', 'l', 'll', 'j', 'z', 't']
    length = lengths[random.randint(0, len(lengths)-1)]
    argschoice = {'' : str(random.randint(0, 2**32 - 1)),
                  'hh' : str(random.randint(0, 2**8 - 1)),
                  'h' : str(random.randint(0, 2**16 - 1)),
                  'l' : str(random.randint(0, 2**32 - 1)),
                  'll' : str(random.randint(0, 2**64 - 1)),
                  'j' : '(uintmax_t)' + str(random.randint(0, 2**64 - 1)),
                  'z' : '(size_t)' + str(random.randint(0, 2**32 - 1)),
                  't' : str(random.randint(0, 2**32 - 1))}
    if width == '*':
        args += str(random.randint(0, 10))
        args += ','
    if precision == '.*':
        args += str(random.randint(0, 10))
        args += ','
    args += argschoice[length] + 'U'
    return ['%' + flag + width + precision + length + utype, args]

testtypes = [rand_int, rand_unsigned, rand_string, rand_chars,
             rand_char, rand_n, pointer]

def make_test(fname):
    fd = open(fname, "w");
    write_header(fd)
    for i in range(2000):
        fmt = "snprintf(buf, LEN, \""
        args = ""
        for j in range(random.randint(0, 20)):
            res = testtypes[random.randint(0,len(testtypes)-1)]()
            fmt += res[0]
            args += res[1]
        fd.write(fmt + "\\n\" " + args + ");\n")
        fd.write("fputs(buf, stdout);\n")
    write_footer(fd)
    fd.close()

def main():
    random.seed()
    test = 0
    fname = "test-printf.c"
    subprocess.call(["make", "clean"])
    subprocess.call(["make", "lPrint.a"])
    for k in range(4):
        make_test(fname)
        run_test(fname, test)
        test += 1;


if __name__ == "__main__":
    main()
  
