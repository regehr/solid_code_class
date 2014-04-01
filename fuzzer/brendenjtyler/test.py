import subprocess
import sys
import random

#seed the PRNG so we can duplicate results
random.seed(1203019)

#how many format options we use per call to printf
optionsPerPrint = 4

#open the file
writeTo = open('test-printf.c', 'w')

#write the beginning of the C file
writeTo.write('#include <math.h>\n#include <stdio.h>\n#include <stdarg.h>\n#include "musl.h"\n\n#define LEN 10000\nchar buf[LEN];\n\nint main (void)\n{\n')

#set up the structures the fuzzer uses
options = ['%d', '%o', '%x', '%ld', '%u', '%lu', '%c', '%s', '%f', '%g', '%e', '%lf', '%lg', '%le']
integers = [2**31-1, -2**31-1]
longs = [2**63-1, -2**63-1]
unsignedInt = [2**32, 0]
unsignedLong = [2**64, 0]
chars = ["' '", "'!'", "'\\\"'", "'#'", "'$'", "'%'", "'&'", "'\\''", "'('", "')'", "'*'", "'+'", "','", "'-'", 
         "'.'", "'/'", "'0'", "'1'", "'2'", "'3'", "'4'", "'5'", "'6'", "'7'", "'8'", "'9'", "':'", "';'", 
         "'<'", "'='", "'>'", "'?'", "'@'", "'A'", "'B'", "'C'", "'D'", "'E'", "'F'", "'G'", "'H'", "'I'", 
         "'J'", "'K'", "'L'", "'M'", "'N'", "'O'", "'P'", "'Q'", "'R'", "'S'", "'T'", "'U'", "'V'", "'W'", 
         "'X'", "'Y'", "'Z'", "'['", "'\\\\'", "']'", "'^'", "'_'", "'`'", "'a'", "'b'", "'c'", "'d'", "'e'", 
         "'f'", "'g'", "'h'", "'i'", "'j'", "'k'", "'l'", "'m'", "'n'", "'o'", "'p'", "'q'", "'r'", "'s'", 
         "'t'", "'u'", "'v'", "'w'", "'x'", "'y'", "'z'", "'{'", "'|'", "'}'", "'~'"]


strings = ['"and"', '"now"', '"for"', '"something"', '"completely"', '"different"']

doubles = [sys.float_info.max, sys.float_info.min, 'INFINITY', '-INFINITY']

#combine all of the values into a list (index corresponds with type for options)
values = [integers, integers, integers, longs, unsignedInt, unsignedLong, chars, strings, doubles, doubles, doubles, doubles, doubles, doubles]

#musl_snprintf(buf, LEN, "format string", value);
#printf("%s\n", buf);
#add the fuzzer code (we'll start with 500 and work from there
for lines in range(0, 1000):

    toWrite = 'musl_snprintf(buf, LEN, "'
    
    #get the options
    indicies = []
    for index in range(0, optionsPerPrint):
        #get the index number we generate so we can match up the options with the thing to print
        option = random.randint(0, len(options)-1)

        indicies.append(option)
        

        #add the options to the string
        toWrite += options[option] + '\\n'

    #close out the options part
    toWrite += '"'

    #add the values to print
    for valueIndex in indicies:
        toWrite += ', ' + str(values[valueIndex][random.randint(0, len(values[valueIndex])-1)]) 

    #close out the line
    toWrite += ');\nprintf("%s\\n", buf);\n\n'

    #add the line to the file
    writeTo.write(toWrite)

#close up the C file
writeTo.write('return 0;\n}\n')
writeTo.close()

#run the make file
subprocess.call(['make'])

#run the executable
subprocess.call(['./test-printf'])
