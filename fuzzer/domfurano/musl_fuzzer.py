import random
import string
import subprocess
import logging
import filecmp
import difflib

maxuint = 2 ** 32
maxint = 2**31 - 1
minint = -(2 ** 31)
max_flag_length = 3
# Large magnitude widths severely slow down printf.
maxwidth = 10
maxprecision = 10
maxstringlength = 10
spec_count_in_file = 100
specifier_flags = {'d': ['-', '+', ' ', '0'],
                   'i': ['-', '+', ' ', '0'],
                   'u': ['-', '0'],
                   'o': ['-', '0', '#'],
                   'x': ['-', '0', '#'],
                   'X': ['-', '0', '#'],
                   'f': ['-', '+', ' ', '0', '#'],
                   'F': ['-', '+', ' ', '0', '#'],
                   'e': ['-', '+', ' ', '0', '#'],
                   'E': ['-', '+', ' ', '0', '#'],
                   'g': ['-', '+', ' ', '0', '#'],
                   'G': ['-', '+', ' ', '0', '#'],
                   'a': ['-', '+', ' ', '0', '#'],
                   'A': ['-', '+', ' ', '0', '#'],
                   'c': ['-'],
                   'C': ['-'],
                   's': ['-'],
                   'S': ['-'],
                   '%': ['%%'],
                   'p': ['-'],
                   'n': ['']}

length_specifiers = {'d': ['', 'hh', 'h', 'l', 'll', 'j', 'z', 't'],
                   'i': ['', 'hh', 'h', 'l', 'll', 'j', 'z', 't'],
                   'u': ['', 'hh', 'h', 'l', 'll', 'j', 'z', 't'],
                   'o': ['', 'hh', 'h', 'l', 'll', 'j', 'z', 't'],
                   'x': ['', 'hh', 'h', 'l', 'll', 'j', 'z', 't'],
                   'X': ['', 'hh', 'h', 'l', 'll', 'j', 'z', 't'],
                   'f': ['', 'L'],
                   'F': ['', 'L'],
                   'e': ['', 'L'],
                   'E': ['', 'L'],
                   'g': ['', 'L'],
                   'G': ['', 'L'],
                   'a': ['', 'L'],
                   'A': ['', 'L'],
                   'c': [''],
                   'C': [''],
                   's': [''],
                   'S': [''],
                   '%': [''],
                   'p': [''],
                   'n': ['', 'hh', 'h', 'l', 'll', 'j', 'z', 't']}

def gen_rand_pointer():
    pointer = '0x'
    for i in range(16):
        pointer += random.choice(string.hexdigits)
    return pointer

def rand_char():
    rc = chr(random.randrange(32, 126))
    if rc == '\\':
        rc = '\\\\'
    if rc == '"':
        rc = '\\"'
    return rc

def rand_string():
    new_string = ""
    for i in range(0, maxstringlength):
        new_string += rand_char()
    return new_string

def gen_rand_float():
    # TO DO
    return ''

def gen_rand_length():
    # TO DO
    return ''

def gen_rand_precision(components):
    precision = random.choice(['', '.*', '.' + str(random.randint(0, maxprecision))])
    if precision == '.*':
        components['precision'] = precision, str(random.randint(0, maxprecision))
    else:
        components['precision'] = precision, ''

def gen_rand_width(components):
    width = random.choice(['', '*', str(random.randint(1, maxwidth))])
    if width == '*':
        components['width'] = width, str(random.randint(1, maxwidth))
    else:
        components['width'] = width, ''

def gen_rand_flags(components):
    components['flags'] = ''.join(random.choice(specifier_flags[components['specifier']]) \
        for i in range(0, random.randint(0, max_flag_length)))

def gen_rand_format_data(components):
    components['specifier'] = random.choice(specifier_flags.keys())
    components['length'] = random.choice(length_specifiers[components['specifier']]) #This data needs to influence values.
    if components['specifier'] == 'd' or components['specifier'] == 'i':
        gen_rand_flags(components)
        gen_rand_width(components)
        gen_rand_precision(components)
        components['values'] = str(random.randint(minint, maxint))
    elif components['specifier'] == 'u' or components['specifier'] == 'o'or \
        components['specifier'] == 'x' or components['specifier'] == 'X':
        gen_rand_flags(components)
        gen_rand_width(components)
        gen_rand_precision(components)
        components['values'] = str(random.randint(0, maxuint)) + 'u'
    elif components['specifier'] == 'f' or components['specifier'] == 'F' or \
        components['specifier'] == 'e' or components['specifier'] == 'E' or \
        components['specifier'] == 'g' or components['specifier'] == 'G' or \
        components['specifier'] == 'a' or components['specifier'] == 'A':
        gen_rand_flags(components)
        gen_rand_width(components)
        gen_rand_precision(components)
        components['values'] = random.choice(['0.0', 'NAN', 'INFINITY', str(random.uniform(-999999999, 999999999))]) # Need to fix this.
    elif components['specifier'] == 'c':
        gen_rand_flags(components)
        gen_rand_width(components)
        components['precision'] = '', ''
        components['values'] = str(random.randrange(0, 255))
    elif components['specifier'] == 's':
        gen_rand_flags(components)
        gen_rand_width(components)
        gen_rand_precision(components)
        components['values'] = '"' + rand_string() + '"'
    elif components['specifier'] == '%':
        gen_rand_flags(components)
        components['width'] = '', ''
        components['precision'] = '', ''
        components['values'] = ''
    elif components['specifier'] == 'p':
        components['flags'] = random.choice(['', '-'])
        components['width'] = '', ''
        components['precision'] = '', ''
        components['values'] = 'p'
    elif components['specifier'] == 'n':
        components['flags'] = ''
        components['width'] = '', ''
        components['precision'] = '', ''
        components['values'] = '&n'
    elif components['specifier'] == 'C':
        components['flags'] = ''
        components['width'] = '', ''
        components['precision'] = '', ''
        components['values'] = '&wi'
    elif components['specifier'] == 'S':
        components['flags'] = ''
        components['width'] = '', ''
        components['precision'] = '', ''
        components['values'] = '&wc'

def gen_rand_snprintf():
    components = {}
    gen_rand_format_data(components)
    snprintf = '    snprintf(buf, LEN, "%' + (random.choice(['1$', '']) if (components['precision'][0]  != '.*' and components['width'][0] != '*') else '')   + \
    components['flags'] + \
    components['width'][0] + \
    components['precision'][0] + \
    components['length'] + \
    components['specifier'] + '"' + \
    (', ' + components['width'][1] if components['width'][0] == '*' else '') + \
    (', ' + components['precision'][1] if components['precision'][0] == '.*' else '') + \
    ('' if components['values'] == '' else ', ' + components['values']) + \
    ');\n    printf ("%s", buf);\n'
    return snprintf

def gen_test_file_header():
    return '\
#include <stdio.h>\n\
#include <math.h>\n\
#include <wchar.h>\n\
\n\
// Thanks, Josh!\n\
#ifdef MUSL\n\
#include "musl.h"\n\
#define snprintf musl_snprintf\n\
#endif\n\
\n\
#define LEN 10000\n\
char buf[LEN];\n\n\
int main(){\n\
    void *p = NULL;\n\
    int n;\n\
    wchar_t wc[10];\n\
    wint_t wi[2];\n\n'

def gen_test_file():
    file_data = gen_test_file_header()
    for i in range(spec_count_in_file):
        file_data += gen_rand_snprintf()
    file_data += '}\n'
    with open('test.c', 'w') as file:
        file.write(file_data)
        file.close()

def gen_musl_local_binaries():
    subprocess.call(['make'])

# Setup logging configuration.
logging.basicConfig(filename='fuzzer.log', level=logging.DEBUG, format='%(asctime)s %(message)s', \
    datefmt='%m/%d/%Y %I:%M:%S %p')

# Generate C file.
gen_test_file()

# Compile musl and local binaries.
gen_musl_local_binaries()

# Execute both binaries and save output.
musl_process = subprocess.Popen(['./test_musl'], stdout = subprocess.PIPE)
local_process = subprocess.Popen(['./test_local'], stdout = subprocess.PIPE)
musl_output = musl_process.communicate()
local_output = local_process.communicate()

with open('musl_output.txt', 'w') as musl_file:
    musl_file.write(musl_output[0])
with open('local_output.txt', 'w') as local_file:
    local_file.write(local_output[0])

musl_return_value = musl_process.wait();
local_return_value = local_process.wait();

# Report difference in binary outputs.
if filecmp.cmp('musl_output.txt', 'local_output.txt') == False:
    print 'Different outputs!'
    musl_file = open('musl_output.txt', 'r')
    local_file = open('local_output.txt', 'r')
    diff = difflib.ndiff(musl_file.readlines(), local_file.readlines())
    delta = ''.join(diff)
    logging.error('\nDifference detected:\n\n' + delta)
    musl_file.close()
    local_file.close()

elif musl_return_value != local_return_value:
    print 'Different return values!'
    logging.error('\nDifference detected:\nmusl return value:' + \
        str(musl_return_value) + '\nlocal return value:' + str(local_return_value))

else:
    print 'No differences detected.'
