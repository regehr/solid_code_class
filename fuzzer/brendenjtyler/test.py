import subprocess
import sys
from random import randint

#open up a file to write to
writeTo = open("hello.c", "w")

#write the headers for the c program
writeTo.write("#include <stdio.h>\r\n")
writeTo.write("\r\n")
writeTo.write("int main (int argc, char **argv)\r\n")
writeTo.write("{\r\n")

#write the printf lines (right now we're doing the highest 1000 ints and trying to print them as chars)
for printLines in range(2**32-1024, 2**32):
    writeTo.write("printf(\"%c\\n\", " + str(printLines) + ");\n")

#close up c program
writeTo.write("}\r\n")

#close the file
writeTo.close()

#compile it (with warning turned off because the compiler complains about int and chars and such)
subprocess.call(["/usr/local/musl/bin/musl-gcc", "hello.c", "-w", "-o", "hello"])

#run it
p = subprocess.Popen(["./hello"], stdout=subprocess.PIPE)

#get the output
out, err = p.communicate()

#turn the output into a list (removing empty entries)
listOut = filter(None, out.split('\n'))

#print out the list
print(listOut)

