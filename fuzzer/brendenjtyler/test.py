import subprocess
import sys
from random import randint

def printHeaders():
    #open up a file to write to
    writeTo = open("hello.c", "w")

    #write the headers for the c program
    writeTo.write("#include <stdio.h>\n")
    writeTo.write("\n")
    writeTo.write("int main (int argc, char **argv)\n")
    writeTo.write("{\n")

    return writeTo
    
def printClose(writeTo):
    #close up c program
    writeTo.write("}\n")

    writeTo.close()

#########################################################
#                                                       #
#                CHARACTER TEST                         #
#                                                       #
#########################################################

writeTo = printHeaders()

#print out the character test for loop
writeTo.write("int i;\n")
writeTo.write("for(i = 0; i < 256; i++)\n")
writeTo.write("{\n")
writeTo.write("printf(\"%c\\n\", (char)i);")
writeTo.write("}\n")

printClose(writeTo)

result = []
for char in range(0, 256):
    result.append(chr(char))

#compile it (with warning turned off because the compiler complains about int and chars and such)
subprocess.call(["/usr/local/musl/bin/musl-gcc", "hello.c", "-w", "-o", "hello"])

#run it
p = subprocess.Popen(["./hello"], stdout=subprocess.PIPE)

#get the output
out, err = p.communicate()

#turn the output into a list (removing empty entries)
listOut = filter(None, out.split('\n'))

for index in range(0, 256):
    if(ord(result[index]) != ord(listOut[index])):
        print("Error at " + str(index) + "\n")
        print("Python char is: " + str(ord(result[index])) + "\n")
        print("C char is: " + str(ord(listOut[index])) + "\n")
        print(result)
        print("")
        print(listOut)
        break

#########################################################
#                                                       #
#                     FLOAT TEST                        #
#                                                       #
#########################################################


writeTo = printHeaders()

#print out the character test for loop
writeTo.write("int i;\n")
writeTo.write("for(i = 0; i < 256; i++)\n")
writeTo.write("{\n")
writeTo.write("printf(\"%c\\n\", (char)i);")
writeTo.write("}\n")

printClose(writeTo)

result = []
for char in range(0, 256):
    result.append(chr(char))

#compile it (with warning turned off because the compiler complains about int and chars and such)
subprocess.call(["/usr/local/musl/bin/musl-gcc", "hello.c", "-w", "-o", "hello"])

#run it
p = subprocess.Popen(["./hello"], stdout=subprocess.PIPE)

#get the output
out, err = p.communicate()

#turn the output into a list (removing empty entries)
listOut = filter(None, out.split('\n'))
