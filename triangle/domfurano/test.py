import subprocess

output = subprocess.check_output(["./triangle", "0", "0", "0", "0", "0", "0"])
if (output != "not a triangle"):
    print("Test failed.")
