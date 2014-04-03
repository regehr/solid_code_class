#!/usr/bin/env python3
#
# Jon Parker
# (c) April Foo' Day
# Fuzzer to fuzz musl printf
#
##########################

import subprocess
import os
import sys
import random

from subprocess import CalledProcessError

def main():

    random.seed(10);
    
    # Specifiers
    d = "d"  # Signed decimal integer
    i = "i"   #	Signed decimal integer
    u = "u" #Unsigned decimal integer	7235
    o = "o" #	Unsigned octal	610
    x = "x" #	Unsigned hexadecimal integer	7fa
    X = "X" #	Unsigned hexadecimal integer (uppercase)	7FA
    f = "f"  #	Decimal floating point, lowercase	392.65
    F = "F" #	Decimal floating point, uppercase	392.65
    e = "e" #	Scientific notation (mantissa/exponent), lowercase	3.9265e+2
    E = "E" #	Scientific notation (mantissa/exponent), uppercase	3.9265E+2
    g = "g" #	Use the shortest representation: %e or %f	392.65
    G = "G" #	Use the shortest representation: %E or %F	392.65
    a = "a" #	Hexadecimal floating point, lowercase	-0xc.90fep-2
    A = "A" #	Hexadecimal floating point, uppercase	-0XC.90FEP-2
    c = "c" #	Character	a
    s = "s" #	String of characters	sample
    p = "p" #	Pointer address	b8000000
    n = "n" #	Nothing printed.
                  #The corresponding argument must be a pointer to a signed int.
                  #The number of characters written so far is stored in the pointed location.	
    percent = "%"# A % followed by another % character will write a single % to the stream.	%
    
    specifiers = [
    d,
    i,
    u,
    o,
    x,
    X,
    f,
    F,
    e,
    E,
    g,
    G,
    a,
    A,
    c,
    s,
    p,
    n,
    percent,
    ]
    
    # Flags
    minus = "-"	#Left-justify within the given field width; Right justification is the default (see width sub-specifier).
    plus = "+"	#Forces to preceed the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a - sign.
    space	= " " #If no sign is going to be written, a blank space is inserted before the value.
    pound = "#"	#Used with o, x or X specifiers the value is preceeded with 0, 0x or 0X respectively for values different than zero.
                        #Used with a, A, e, E, f, F, g or G it forces the written output to contain a decimal point even if no more digits follow.
                        #By default, if no digits follow, no decimal point is written.
    zero = "0"	#Left-pads the number with zeroes (0) instead of spaces when padding is specified (see width sub-specifier).
    
    flags = [ minus, plus, space, pound, zero, ""]
    
    #Trigraphs - Shouldn't be relevant here, but always an edge case for compilers, so what the hell.
    t1 = "??="
    t2 = "??/"
    t3 = "??'"
    t4 = "??("
    t5 = "??)"
    t6 = "??!"
    t7 = "??<"
    t8 = "??>"
    t9 = "??-"

    # width
    width = "*"
    
    # precision
    precision1 = ".*"
    precision2 = "."

    #length
    #(none)	int	unsigned int	double	int	char*	void*	int*
    hh	= "hh"#signed char	unsigned char					signed char*
    h = "h"	#short int	unsigned short int					short int*
    l = "l"	#long int	unsigned long int		wint_t	wchar_t*		long int*
    ll = "ll"	#long long int	unsigned long long int					long long int*
    j = "j"	#intmax_t	uintmax_t					intmax_t*
    z = "z"	#size_t	size_t					size_t*
    t = "t"	#ptrdiff_t	ptrdiff_t					ptrdiff_t*
    L = "L"	#		long double
    
    lengths = [
    hh,
    h,
    l,
    ll,
    j,
    z,
    t,
    L,
    ]
    
    # compatabilities = { key : value, key : value, key:value }
    #{ key : { el1, el2, el3}, key : {el5, el1, eldiablo} }
    compatabilities = {
    d : [ hh, h, l, ll, j, z, t, "" ],
    i : [ hh, h, l, ll, j, z, t, "" ],
    u : [ hh, h, l, ll, j, z, t, "" ],
    o : [ hh, h, l, ll, j, z, t, "" ],
    x : [ hh, h, l, ll, j, z, t, "" ],
    X : [ hh, h, l, ll, j, z, t, "" ],
    f : [ L, "" ],
    F : [ L, "" ],
    e : [ L, "" ],
    E : [ L, "" ],
    g : [ L, "" ],
    G : [ L, "" ],
    a : [ L, "" ],
    A : [ L, "" ],
    c : [ l, "" ],
    s : [ "", "" ],
    p : [ "" ],
    n : [ hh, h, l, ll, j, z, t, "" ],
    percent : [ "" ],
    }
    
    ranges = {
    d : [-2147483648, 2147483647],
    i : [-2147483648, 2147483647],
    u :  [0, 4294967295],
    o : [0, 4294967295],
    x : [0, 4294967295],
    X : [0, 4294967295],
    f : [sys.float_info.min, sys.float_info.max],
    F : [sys.float_info.min, sys.float_info.max],
    e : [sys.float_info.min, sys.float_info.max],
    E : [sys.float_info.min, sys.float_info.max],
    g : [sys.float_info.min, sys.float_info.max],
    G : [sys.float_info.min, sys.float_info.max],
    a : [sys.float_info.min, sys.float_info.max],
    A : [sys.float_info.min, sys.float_info.max],
    c : [ 0, 255 ],
    s : [ "bad", "bad"],
    p : [0, 4294967295],
    n : [ "bad", "bad" ],
    percent : [ "bad", "bad" ],
    }

    # C file.
    sfuzzball = "test-printf.c"

    for i in range(0, 1):
        with open(sfuzzball, 'w+') as fuzzball:
            fuzzball.write(r"""#include <stdio.h>
#include <stdarg.h>
#include "musl.h"

#define LEN 10000
char buf[LEN];

int main (void)
{
    long long int x;
    long long int* pointer = &x;
""")
            for lines in range(0, 2000):                         
                    fuzzball.write(r"""
    musl_snprintf (buf, LEN, """ + "\"")
                    valuesLength = random.randint(1,10)
                    values = [0]*valuesLength*3
                    valueCount = 0;
                    for specifier in range(0, valuesLength-1):
                        token = specifiers[random.randint(0, len(specifiers)-1)]
                        values[valueCount] = 0;
                        length = compatabilities[token][random.randint(0, len(compatabilities[token]) - 1)]
                        flag = flags[random.randint(0, len(flags) -1)]
                                           
                        
                        if (token != n and token != percent):
                            width = str(random.randint(-255, 255))
                            if random.randint(0, 7) == 7:
                                width = ""
                            if random.randint(0, 7) == 7:
                                width = str(random.randint(-sys.maxsize - 1, sys.maxsize))
                            if random.randint(0, 7) == 7:
                                width = "*"
                                values[valueCount] = str(random.randint(-255, 255))
                                valueCount = valueCount + 1
                            #if random.randint(0, 7) == 7:
                            #    width = "*"
                            #    values[valueCount] = str(random.randint(-sys.maxsize - 1, sys.maxsize))
                            #    valueCount = valueCount + 1
                            
                            precision = "." + str(random.randint(-255, 255))
                            if random.randint(0, 7) == 7:
                                precision = ""
                            if random.randint(0, 7) == 7:
                                precision = str(random.randint(-sys.maxsize - 1, sys.maxsize))
                            if random.randint(0, 7) == 7:
                                precision = ".*"
                                values[valueCount] = str(random.randint(-255, 255))
                                valueCount = valueCount + 1
                            #if random.randint(0, 7) == 7:
                            #    precision = ".*"
                            #    values[valueCount] = str(random.randint(-sys.maxsize - 1, sys.maxsize))
                            #    valueCount = valueCount + 1
                        else:
                            width = ""
                            precision = ""
                            
                        if length == "L":
                            randomNumber = random.randint(0, 4)
                            floatValue = "0.0"
                            if randomNumber == 0:
                                floatValue = "(long double) %f" %random.uniform(sys.float_info.min, sys.float_info.max)
                            elif randomNumber == 1:
                                floatValue = "(long double) (1.0/0.0)"
                            elif randomNumber == 2:
                                floatValue = "(long double) (-1.0/0.0)"
                            elif randomNumber == 3:
                                floatValue = "(long double) -0.0"
                            elif randomNumber == 4:
                                floatValue = "(long double) (0.0/0.0)"
                            values[valueCount] = floatValue
                            valueCount = valueCount + 1
                        elif ranges[token][0] == sys.float_info.min:
                            randomNumber = random.randint(0, 4)
                            floatValue = "0.0"
                            if randomNumber == 0:
                                floatValue = "%f" %random.uniform(sys.float_info.min, sys.float_info.max)
                            elif randomNumber == 1:
                                floatValue = "1.0/0.0"
                            elif randomNumber == 2:
                                floatValue = "-1.0/0.0"
                            elif randomNumber == 3:
                                floatValue = "-0.0"
                            elif randomNumber == 4:
                                floatValue = "0.0/0.0"
                            values[valueCount] = floatValue
                            valueCount = valueCount + 1
                        elif ranges[token][0] != "bad":
                            values[valueCount] = random.randint(ranges[token][0], ranges[token][1]);
                            valueCount = valueCount + 1
                        elif token == s:
                            values[valueCount] = "\"ick\""
                            valueCount = valueCount + 1
                        elif token == n:
                            values[valueCount] = "pointer"
                            valueCount = valueCount + 1
                        elif token == percent:
                            pass
                        else:
                            pass         
                        
                        fuzzball.write("%" + flag + width + precision + length + token)
                    fuzzball.write("\"")
                    for valueIndex in range(0, valueCount):
                        fuzzball.write(", " + str(values[valueIndex]))
#                    fuzzball.write(""");
#      printf ("%s", buf);""")
                    fuzzball.write(""");
        printf("%1$*2$.*3$i",2,2,2);""")
  
            fuzzball.write(r"""  
  return 0;
}
""")

if __name__ == '__main__':
	main()

