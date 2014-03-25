import subprocess
import sys
import random
import os
import string

#################Can't get musl to work yet#############################

#Initial Hello World Test Case
def helloTest():
    output = "Hello World"
    with open("hello.c", "w") as file:
        file.write("#include<stdio.h>\nint main(){return printf(\"" + output + "\");}")
        file.close()
    subprocess.call(["gcc", "hello.c", "-o", "hello"])
    #subprocess.call(["musl-gcc", "-static", "hello.c", "-o", "muslHello"])
    with open('hello.txt', 'w') as t:
        test1 = subprocess.call(["./hello"], stdout=t)

    os.remove("hello.c")
    os.remove("hello")

    print "Hello World  Test Passed"

#Generate a large random string
def randomString(size = 4096, ranString = string.ascii_uppercase + string.digits):
    return ''.join(random.choice(ranString) for n in range(size))

#Int test pulled from another fuzzer
def intTest():
    for i in xrange(-5, 10):
        with open("test.c", "w") as file:
            file.write("#include<stdio.h>\nint main(){return printf(\"" + "%d" + "\"," + str(i) + ");}")
            file.close()

        subprocess.call(["gcc", "test.c", "-o", "test"])
        #subprocess.call(["musl-gcc", "-static", "test.c", "-o", "muslTest"])

        with open('test.txt', 'w') as t:
            test1 = subprocess.call(["./test"], stdout=t)
    #with open('musl.txt', 'w') as m:
        #test2 = subprocess.call(["./muslTest"], stdout=m)

    #if test1 != test2 or filecmp.cmp('test.txt', 'musl.txt') == False:
        #print "Test Failed"
        #exit()


    os.remove("test.c")
    os.remove("test")
    #os.remove("muslTest")

    print "Int Test Passed"

#Random String Test to see if printf can handle a large random string
def stringTest():
    output = randomString()
    with open("tester.c", "w") as file:
        file.write("#include<stdio.h>\nint main(){return printf(\"" + output + "\");}")
        file.close()
    subprocess.call(["gcc", "tester.c", "-o", "tester"])
    with open('tester.txt', 'w') as t:
        test1 = subprocess.call(["./tester"], stdout=t)

    os.remove("tester.c")
    os.remove("tester")

    print "Random String Test Passed"

#Special Character Test to see if printf can handle special chars
def charTest():
    output = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&'()*+,-./:;<=>?@[\]^_`{|}"
    with open("chartester.c", "w") as file:
        file.write("#include<stdio.h>\nint main(){return printf(\"" + output + "\");}")
        file.close()
    subprocess.call(["gcc", "chartester.c", "-o", "chartester"])
    with open('chartester.txt', 'w') as t:
        test1 = subprocess.call(["./chartester"], stdout=t)

    os.remove("chartester.c")
    os.remove("chartester")

    print "Special Char Test Passed"


if __name__ == "__main__":
    intTest()
    stringTest()
    charTest()

