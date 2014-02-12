#! /usr/bin/python27

import os
import random
import sys
import unittest
import subprocess
import multiprocessing
import filecmp
import string
import shutil

TEST_COUNT = 20

# Set-up tests
class MyTestCase(unittest.TestCase):
    def setUp(self):
        pass


# Checks that input file = output file
class FileEquality(MyTestCase):
    def runTest(self):
        char_set = string.ascii_uppercase + string.digits
        for n in range(1, TEST_COUNT + 1):
            testFile = open('random.txt', 'r+')
            #print "test file" + str(testFile.read())
            testFile.write( ''.join(random.sample(char_set*n,n)))
            testFile.write('\n')
            testFile.close()
            shutil.copy('random.txt', 'old.txt') #copy file since it will be overwritten     
            outPut = open('output.txt', 'w')
            rslt1 = subprocess.call(['./huff', '-c', 'random.txt'], stdout=outPut)
            outPut.close()
            rslt2 = subprocess.call(['./huff', '-d', 'random.txt.huff'])        
            self.assertTrue(filecmp.cmp('random.txt', 'old.txt'))


# Counts number of lines in generated table
class HuffTableCount(MyTestCase):
    def runTest(self):
        char_set = string.ascii_uppercase + string.digits
        for n in range(1, TEST_COUNT + 1):
            testFile = open('random.txt', 'w')
            testFile.write( ''.join(random.sample(char_set*n,n)))
            testFile.close()
            table = open('random.table', 'w')
            rslt = subprocess.call(['./huff', '-t', 'random.txt'], stdout=table)
            table.close()
            numLines = sum(1 for line in open('random.table'))
            self.assertEqual(256, numLines) 
                

# Exit status is zero is successful  
class ExitCompressGood(MyTestCase):
    def runTest(self):
        char_set = string.ascii_uppercase + string.digits
        for n in range(1, TEST_COUNT + 1):
            testFile = open('random.txt', 'w')
            testFile.write( ''.join(random.sample(char_set*n,n)))
            testFile.close()
            shutil.copy('random.txt', 'old.txt') #copy file since it will be overwritten
            outPut = open('output.txt', 'w')
            rslt = subprocess.call(['./huff', '-c', 'random.txt'], stdout=outPut)
            outPut.close()
            self.assertEqual(0, rslt) # successful
                

# Exit status is zero is successful  
class ExitDecompressGood(MyTestCase):
    def runTest(self):
        char_set = string.ascii_uppercase + string.digits
        for n in range(1, TEST_COUNT + 1):
            testFile = open('random.txt', 'w')
            testFile.write( ''.join(random.sample(char_set*n,n)))
            testFile.write('\n')
            testFile.close()
            shutil.copy('random.txt', 'old.txt') #copy file since it will be overwritten
            outPut = open('output.txt', 'w') 
            subprocess.call(['./huff', '-c', 'random.txt'], stdout=outPut)
            outPut.close()
            rslt = subprocess.call(['./huff', '-d', 'random.txt.huff'])        
            self.assertEqual(0, rslt) # successful 
                

# Exit status is 255 if unsuccessful  
class ExitDecompressBad(MyTestCase):
    def runTest(self):
        char_set = string.ascii_uppercase + string.digits
        for n in range(1, TEST_COUNT + 1):
            testFile = open('random.txt', 'w')
            testFile.write( ''.join(random.sample(char_set*n,n)))
            testFile.close()
            shutil.copy('random.txt', 'random.huff') #random.huff doesn't have magic key
            rslt = subprocess.call(['./huff', '-d', 'random.huff'])        
            self.assertEqual(255, rslt) # unsuccessful -- not a compressed file
                


def main():

    suite = unittest.TestSuite()    
    runner = unittest.TextTestRunner(verbosity=2)

    fe = FileEquality()
    ht = HuffTableCount()
    ecg = ExitCompressGood()
    edg = ExitDecompressGood()
    edb = ExitDecompressBad()
    suite.addTests([ht, fe, ecg, edg, edb])

    #os.chdir('../')
    # run the tests
    runner.run(suite)
    


if __name__ == '__main__':
    sys.exit(main())
