from subprocess import call
import os

#switch to the directory with the test files in it
os.chdir("test/testFiles")

#remote the .tbl files (this has to be run in a shell for the wildcard to work correctly)
call(["sh", "-c", "rm *.tbl"])
call(["rm", "huff"])
