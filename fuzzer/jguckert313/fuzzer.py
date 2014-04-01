import random
import subprocess
def fuzzInts():
	f = open("int_fuzz.c", "w")
	f.write("#include<stdio>\n")
	f.write("int main() {\r")
	
	for i in range(1, 10000):
		d = str(random.seed(i))
		f.write("\tprintf(%d," + d + ");\n")
	
	f.write("return 0;\r}")
	f.close
	subprocess.call("./musl-gcc -static ../../solid_code_class/fuzzer/jguckert313/int_fuzz.c -o muslintfuzz")
	subprocess.call("gcc ../../solid_code_class/fuzzer/jguckert313/int_fuzz.c -o gccintfuzz")
	subprocess.call("./muslintfuzz > muslintfuzz.txt")
	subprocess.call("./gccintfuzz > gccintfuzz.txt")
	subprocess.call("diff gccintfuzz.txt muslintfuzz.txt")

def main():
	fuzzInts()

main()
