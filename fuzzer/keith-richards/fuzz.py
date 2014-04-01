#! /usr/bin/env python27
        
# def generate_test_case():
#     specifiers = ['d','i','u','o','x','X','f','F','e','E','g','G','a','A','c','s','p','n','%']
#     width = [str(x) for x in range(15)]
#     flags = ['+','-','0','#',' ']
#     length = ['h','hh','l','ll','j','z','t','L']
    
#     all_lists = [specifiers, width, flags, length]
#     for f in list(itertools.product(*all_lists))[:5000]:
#         yield '%' + ''.join(f) + str(random.randint(1, 10))

import os
import sys
import random
import unittest
import itertools
import select
import types
import uuid

try:
    import cffi
except ImportError:
    print "need cffi python module"
    print "wget https://pypi.python.org/packages/source/c/cffi/cffi-0.8.2.tar.gz#md5=37fc88c62f40d04e8a18192433f951ec"
    exit(1)

class Environment():
    def __init__(self, sh_lib):
        self.ffi = cffi.FFI()
        self.ffi.dlopen(sh_lib)
        self.ffi.cdef("int printf(const char *format, ...);")
        self.c_lib = self.ffi.verify()
        self.current_arg = None
        self.current_type = None
        self.result = None
        self.reader, self.writer = os.pipe()
        self.old_std = None
        self.formats = {"int"     : "%d\n",
                        "float"   : "%f\n",
                        "char[]"  : "%s\n"}

    def mk_primative(self, arg, _type):
        self.current_type = _type
        self.current_arg = self.ffi.cast(_type, arg)

    def mk_string(self, arg):
        self.current_type = "char[]"
        self.current_arg = self.ffi.new("char[]", arg)

    def _capture(self):
        sys.stdout.write(' \b')
        self.old_std = os.dup(1)
        os.dup2(self.writer, 1)

    def printf(self):
        self._capture()
        self.c_lib.printf(self.formats[self.current_type], self.current_arg)
        return self._flush()

    def _flush(self):
        out = ''
        while self._more_data():
                out += os.read(self.reader, 1024)
        os.dup2(self.old_std, 1)
        return out

    def _more_data(self):
        return bool(select.select([self.reader], [], [], 0)[0])

    @staticmethod
    def clean():
        cffi.verifier.cleanup_tmpdir()


class Test_Case(unittest.TestCase):
    def __init__(self, case, oracle, result):
        super(unittest.TestCase, self).__init__()
        self._cleanups = None
        self._testMethodDoc = None
        self._testMethodName = "runTest"
        self.case = case
        self.oracle = oracle
        self.result = result

    def runTest(self):
        self.assertTrue(self.oracle == self.result, "Command: %s\nExpected: %s\nActual: %s" % \
                            (self.case, self.oracle, self.result))


def generate_int_tests(oracle, lib):
    for i in range(500):
        num = random.randint(-2147483646, 2147483647)
        oracle.mk_primative(num, "int")
        lib.mk_primative(num, "int")

        expect = oracle.printf()
        actual = lib.printf()

        test = Test_Case('', expect, actual)
        yield test

def generate_float_tests(oracle, lib):
    for i in range(500):
        num = random.uniform(-2147483646, 2147483647)
        oracle.mk_primative(num, "float")
        lib.mk_primative(num, "float")

        expect = oracle.printf()
        actual = lib.printf()

        test = Test_Case('', expect, actual)
        yield test

def generate_str_tests(oracle, lib):
    for i in range(500):
        string = str(uuid.uuid4())
        oracle.mk_string(string)
        lib.mk_string(string)

        expect = oracle.printf()
        actual = lib.printf()

        test = Test_Case('', expect, actual)
        yield test
    
    
def generate_all_tests(oracle, lib):
    return itertools.chain(generate_int_tests(oracle, lib),
                           generate_float_tests(oracle, lib),
                           generate_str_tests(oracle, lib))

def main(_lib):
    oracle = Environment(None) # default libc.so.6 (system C code)
    lib   = Environment(_lib) # lib you want to fuzz

    suite = unittest.TestSuite()
    runner = unittest.TextTestRunner(verbosity=2)

    suite.addTests(generate_all_tests(oracle, lib))
    runner.run(suite)

    Environment.clean()
    return 0

if __name__ == '__main__':
    if len(sys.argv) != 2 or not os.path.isfile(sys.argv[1]):
        print "usage: python27 fuzz.py <path_to_libc.so_to_fuzz>"
        exit(1)
    sys.exit(main(sys.argv[1]))



