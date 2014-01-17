#!usr/bin/python3

from subprocess import call
import os

def listdir_nohidden(path):
    for f in os.listdir(path):
        if not f.startswith('.') and not f.endswith(".pl") and not f.endswith(".txt"):
            yield f

#get the list of directories
students = listdir_nohidden("..")

#get the absolute path of the repo
directory = os.path.abspath("..")

#for each person's directory
for name in students:
    #switch to each directory
    os.chdir(directory + "/" + name)

    #build it
    os.system("make all")

    #copy the executable to my directory
    os.system("cp triangle " + directory + "/brendenjtyler/triangle")

    #clean up their directory
    os.system("make clean")

    #switch back to my directory
    os.chdir(directory + "/brendenjtyler")

    #put their name in the file
    output = open("tests.txt", "a")
    output.write(name + "\n")
    output.close()

    #run the test file
    os.system("make test >> tests.txt")

    #clean up my directory
    os.system("make superclean")
