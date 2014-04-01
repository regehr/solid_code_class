#! /usr/bin/env python27

import os
import sys
import argparse
import subprocess
import tempfile
import unittest
from generator import printf_generator

TEST_ITERATIONS = 54
PRINTFS_IN_FILE = 200
O_BIN = './oracle_binary'
T_BIN = './test_binary'

class Test_Case(unittest.TestCase):
    def __init__(self, oracle, result, commands):
        self._testMethodName = 'runTest'
        self._testMethodDoc = None
        self._cleanups = None
        self.oracle = oracle
        self.result = result
        self.commands = commands

    def runTest(self):
        for i, command in enumerate(self.commands):
            self.assertTrue(self.result[i] == self.oracle[i], \
                                "\nCommand: %s\nExpected: %s\nActual:   %s" \
                                % (command.replace('\n', ''), self.oracle[i], self.result[i]))

def generate_printfs_for_c_file(printf):
    commands = []
    with tempfile.NamedTemporaryFile(suffix='.c', delete=False) as tmp:
        tmp.write('\n#include <stdio.h>\nint main(void) {\n')
        for i in xrange(PRINTFS_IN_FILE):
            try:
                random_printf = next(printf)
            except StopIteration:
                printf = printf_generator()
                random_printf = next(printf)
            tmp.write(random_printf)
            tmp.write('\n')
            commands.append(random_printf)
        tmp.write('return 0;\n}\n')
    return (tmp.name, commands)

def run_against_libc(c_file):
    try:
        _ = subprocess.check_output(['gcc', c_file,'-o', O_BIN])
        output = subprocess.check_output([O_BIN])
        return output.splitlines()
    except OSError:
        print 'Error with compiling and/or exec'
        exit(-1)

def run_against_musl(c_file):
    try:
        _ = subprocess.check_output(['gcc', 'fwrite.c', 'snprintf.c', 'vfprintf.c', 'vsnprintf.c', c_file,'-o', T_BIN])
        output = subprocess.check_output([T_BIN])
        return output.splitlines()
    except OSError:
        print 'Error with compiling and/or exec'
        exit(-1)

def main(delete):
    suite = unittest.TestSuite()
    gen = printf_generator()
    for i in xrange(TEST_ITERATIONS):
        sys.stdout.write('\rbuilding tests %.02f%%' % (float(i) / float(TEST_ITERATIONS) * 100))
        sys.stdout.flush()
        
        c_file, printfs = generate_printfs_for_c_file(gen)
        if not delete:
            print c_file
            
        oracle = run_against_libc(c_file)
        result = run_against_musl(c_file)
            
        test = Test_Case(oracle, result, printfs)
        suite.addTest(test)
            
        if delete:
            os.remove(c_file)

    sys.stdout.write('\rTest Building Complete. Running ...\n')
    sys.stdout.flush()

    os.remove(O_BIN)
    os.remove(T_BIN)

    runner = unittest.TextTestRunner(verbosity=2)
    runner.run(suite)

    return 0;

if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='fuzz musl printf function')
    parser.add_argument('-d', action='store_false', default=True)
    
    args = parser.parse_args()
    sys.exit(main(args.d))
