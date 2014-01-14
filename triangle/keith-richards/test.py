#! /usr/bin/env python

import os
import random
import sys
import unittest
import subprocess

NUM_OF_TESTS = 500
EXECUTABLE = './triangle'
START_X = 2


# every test case inherits this setup method
class MyTestCase(unittest.TestCase):
    def setUp(self):
        pass

class IsoscelesRight500Cases(MyTestCase):
    def runTest(self):
        for i in range(START_X, NUM_OF_TESTS + START_X):
            input = [str(START_X), str(START_X), str(START_X), str(i*i), str(i*i), str(i*i)]
            output = subprocess.check_output([EXECUTABLE] + input)
            self.assertTrue(output == 'isosceles right\n', 
                            '\nexpected: isosceles right\nactual  : %s\ninput   : %s' % (output, ' '.join(input)))


class ScaleneRight500Cases(MyTestCase):
    def runTest(self):
        for i in range(START_X, NUM_OF_TESTS + START_X):
            input = [str(START_X), str(START_X), str(START_X), str(i*i), str(i*i*i), str(i*i)]
            output = subprocess.check_output([EXECUTABLE] + input)
            self.assertTrue(output == 'scalene right\n', 
                            '\nexpected: scalene right\nactual  : %s\ninput   : %s' % (output, ' '.join(input)))


class IsoscelesAcute500Cases(MyTestCase):
    def runTest(self):
        for i in range(START_X, NUM_OF_TESTS + START_X):
            input = [str(START_X), str(START_X), str(START_X*2), str((i*i)+1), str(START_X*3), str(START_X)]
            output = subprocess.check_output([EXECUTABLE] + input)
            self.assertTrue(output == 'isosceles acute\n', 
                            '\nexpected: isosceles acute\nactual  : %s\ninput   : %s' % (output, ' '.join(input)))


class ScaleneAcute500Cases(MyTestCase):
    def runTest(self):
        for i in range(START_X, NUM_OF_TESTS + START_X):
            input = [str(START_X), str(START_X), str((START_X*2)-1), str(i*i*i), str(START_X*3), str(START_X)]
            output = subprocess.check_output([EXECUTABLE] + input)
            self.assertTrue(output == 'scalene acute\n', 
                            '\nexpected: scalene acute\nactual  : %s\ninput   : %s' % (output, ' '.join(input)))


class IsoscelesObtuse500Cases(MyTestCase):
    def runTest(self):
        mid_point = 1000000
        for i in range(START_X, NUM_OF_TESTS + START_X):
            input = [str(mid_point-i), str(START_X-1), str(mid_point), str(START_X), str(mid_point+i), str(START_X-1)]
            output = subprocess.check_output([EXECUTABLE] + input)
            self.assertTrue(output == 'isosceles obtuse\n', 
                            '\nexpected: isosceles obtuse\nactual  : %s\ninput   : %s' % (output, ' '.join(input)))


class ScaleneObtuse500Cases(MyTestCase):
    def runTest(self):
        for i in range(START_X, NUM_OF_TESTS + START_X):
            input = [str(START_X), str(START_X), str((START_X*2)), str(START_X*2), str(i*5), str(START_X)]
            output = subprocess.check_output([EXECUTABLE] + input)
            self.assertTrue(output == 'scalene obtuse\n', 
                            '\nexpected: scalene obtuse\nactual  : %s\ninput   : %s' % (output, ' '.join(input)))


class NotATriangle500Cases(MyTestCase):
    def runTest(self):
        for i in range(NUM_OF_TESTS/2):
            input = [str(i), str(i), str(i), str(i), str(i), str(i)]
            output = subprocess.check_output([EXECUTABLE] + input)
            self.assertTrue(output == 'not a triangle\n', 
                            '\nexpected: not a triangle\nactual  : %s\ninput   : %s' % (output, ' '.join(input)))
        for i in range(NUM_OF_TESTS/2):
            input = [str(i), str(i), str(i), str(i), str(i+1), str(i+1)]
            output = subprocess.check_output([EXECUTABLE] + input)
            self.assertTrue(output == 'not a triangle\n', 
                            '\nexpected: not a triangle\nactual  : %s\ninput   : %s' % (output, ' '.join(input)))


class Fuzz1000Cases(MyTestCase):
    def runTest(self):
        try:
            for i in range(500):
                ints = [random.randint(0, 10) for y in range(6)]
                input = [str(ints[0]), str(ints[1]), str(ints[2]), str(ints[3]), str(ints[4]), str(ints[5])]
                subprocess.check_call([EXECUTABLE] + input, stdout=open('/dev/null'))
            for i in range(500):
                ints = [random.randint(0, 2000000000) for y in range(6)]
                input = [str(ints[0]), str(ints[1]), str(ints[2]), str(ints[3]), str(ints[4]), str(ints[5])]
                subprocess.check_call([EXECUTABLE] + input, stdout=open('/dev/null'))
        except:
            self.fail('execution failed on input %s' % ' '.join(input))
            raise 


def main():

    # initialize unit tests and harness

    suite = unittest.TestSuite()    
    runner = unittest.TextTestRunner(verbosity=2)

    ir = IsoscelesRight500Cases()
    sr = ScaleneRight500Cases()
    ia = IsoscelesAcute500Cases()
    sa = ScaleneAcute500Cases()
    io = IsoscelesObtuse500Cases()
    so = ScaleneObtuse500Cases()
    nt = NotATriangle500Cases()
    fuzz = Fuzz1000Cases()

    suite.addTests([ir, sr, ia, sa, io, so, nt, fuzz])

    # run the tests
    runner.run(suite)
    


if __name__ == '__main__':
    sys.exit(main())
