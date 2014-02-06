from subprocess import call

#remove the directory that has all of the test files in it
call(["rm", "-r", "testFiles"])

#replace it with a clean one
call(["mkdir", "testFiles"])
