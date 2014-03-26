import subprocess
import sys
import random
import os
import string
import filecmp

#Initial Hello World Test Case
def helloTest():
    output = "Hello World"
    with open("hello.c", "w") as file:
        file.write("#include<stdio.h>\nint main(){return printf(\"" + output + "\");}")
        file.close()
    subprocess.call(["gcc", "hello.c", "-o", "hello"])
    subprocess.call(["/home/tojohnso/musl-1.0.0/musl/bin/musl-gcc", "-static", "hello.c", "-o", "muslHello"])
    with open('hello.txt', 'w') as t:
        test1 = subprocess.call(["./hello"], stdout=t)
    with open('muslHello.txt', 'w') as m:
        test2 = subprocess.call(["./muslHello"], stdout=m)

    if test1 != test2 or filecmp.cmp('hello.txt', 'muslHello.txt') == False:
        print "Test Failed"
        exit()

    os.remove("hello.c")
    os.remove("hello")
    os.remove("muslHello")

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
        subprocess.call(["/home/tojohnso/musl-1.0.0/musl/bin/musl-gcc", "-static", "test.c", "-o", "muslTest"])

        with open('test.txt', 'w') as t:
            test1 = subprocess.call(["./test"], stdout=t)
        with open('musl.txt', 'w') as m:
            test2 = subprocess.call(["./muslTest"], stdout=m)

        if test1 != test2 or filecmp.cmp('test.txt', 'musl.txt') == False:
            print "Test Failed"
            exit()


        os.remove("test.c")
        os.remove("test")
        os.remove("muslTest")

    print "Int Test Passed"

#Random String Test to see if printf can handle a large random string
def stringTest():
    output = randomString()
    with open("tester.c", "w") as file:
        file.write("#include<stdio.h>\nint main(){return printf(\"" + output + "\");}")
        file.close()
    subprocess.call(["gcc", "tester.c", "-o", "tester"])
    subprocess.call(["/home/tojohnso/musl-1.0.0/musl/bin/musl-gcc", "-static", "tester.c", "-o", "muslTester"])
    with open('tester.txt', 'w') as t:
        test1 = subprocess.call(["./tester"], stdout=t)
    with open('mucltester.txt', 'w') as mt:
        test2 = subprocess.call(["./muslTester"], stdout=mt)

    os.remove("tester.c")
    os.remove("tester")
    os.remove("muslTester")

    print "Random String Test Passed"

#Special Character Test to see if printf can handle special chars
def charTest():
  
    output = "!#$%&()*+,-./:;<=>?@[\]^_{|}"

    with open("test4.c", "w") as file:
        file.write("#include<stdio.h>\nint main(){return printf(\"" + output + "\");}")
        file.close()
    subprocess.call(["gcc", "test4.c", "-o", "chartest"])
    subprocess.call(["/home/tojohnso/musl-1.0.0/musl/bin/musl-gcc", "-static", "test4.c", "-o", "muslChar"])
    with open('test4.txt', 'w') as t:
        test1 = subprocess.call(["./chartest"], stdout=t)
    with open('muslChar.txt', 'w') as m:
        test2 = subprocess.call(["./muslChar"], stdout=m)

    if test1 != test2 or filecmp.cmp('test4.txt', 'muslChar.txt') == False:
        print "Test Failed"
        exit()
  

    os.remove("test4.c")
    os.remove("chartest")
    os.remove("muslChar")

    print "Special Char Test Passed"





if __name__ == "__main__":
    helloTest()
    intTest()
    stringTest()
    charTest()    
    

