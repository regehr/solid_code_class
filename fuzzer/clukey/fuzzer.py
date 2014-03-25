#!/usr/local/bin/python3
#
# Fuzzer for musl vfprintf
#
# Student: John Clukey

import subprocess


if __name__ == "__main__":
    test = 0
    exname = "fuzzfile" + str(test)
    fname = exname + ".c"
    fd = open(fname, "w");
    fd.write("#include <stdio.h>\n")
    fd.write("\n")
    fd.write("int main () {\n")
    fd.write("fprintf(stdout, \"Hello World\");\n")
    fd.write("return 0;\n")
    fd.write("}\n")
    fd.close()
    muslresult = subprocess.check_output(["musl-gcc",
                                      "-static",
                                      "-g",
                                      "-O0",
                                      fname])
    muslresult = subprocess.check_output(["./a.out"])
    normlresult = subprocess.check_output(["musl-gcc",
                                          "-static",
                                          "-g",
                                          "-O0",
                                          fname])
    normlresult = subprocess.check_output(["./a.out"])
    if muslresult != normlresult:
        subprocess.call(["mv", fname, "./fuzzfails/"+fname])
    else:
        subprocess.call(["rm", "a.out"])
        subprocess.call(["rm", fname])
        test+=1

# More to come
