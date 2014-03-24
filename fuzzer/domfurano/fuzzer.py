import subprocess
import string
import random
import os
import filecmp
import logging

def rand_string(length):
    "Returns a random string of ascii characters of size 'length'."
    new_string = ""
    for i in range(0, length):
        new_string += chr(random.randrange(48, 57))
    return new_string

def generate_c_file(specifier, input):
    with open("test.c", "w") as file:
        file.write("#include<stdio.h>\nint main(){return printf(\"" + specifier + "\"," + str(input) + ");}")
        file.close()

def compile_c_files():
    subprocess.call(["gcc", "test.c", "-o", "GNU_test"])
    subprocess.call(["musl-gcc", "-static", "test.c", "-o", "musl_test"])

def delete_c_file():
    os.remove("test.c");

def delete_compiled_files():
    os.remove("GNU_test")
    os.remove("musl_test")

# Setup logging configuration.
logging.basicConfig(filename='fuzzer.log', level=logging.DEBUG, format='%(asctime)s %(message)s', datefmt='%m/%d/%Y %I:%M:%S %p')

for i in xrange(-2147483648, 2147483648):
    generate_c_file("%d", i)
    compile_c_files()
    with open('GNU_output.txt', 'w') as f1:
        output1 = subprocess.call(["./GNU_test"], stdout=f1)
    with open('musl_output.txt', 'w') as f2:
        output2 = subprocess.call(["./musl_test"], stdout=f2)

    if output1 != output2 or filecmp.cmp('GNU_output.txt', 'musl_output.txt') == False:
        print "An error has occurred!"
        logging.warning("\tprintf return values may differ!\n" + "\t\t\tGNU ouput:\t" + str(output1) + "\n\t\t\tmusl output:\t" + str(output2))
        exit()

    delete_c_file()
    delete_compiled_files()

print "All tests passed."
