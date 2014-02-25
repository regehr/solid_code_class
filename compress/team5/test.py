#! /usr/bin/python27

import os
import subprocess
import unittest
import sys
import shutil
import filecmp
import math
from subprocess import call



class TestCases(unittest.TestCase):
	def setUp(self):		
		self.seq = range(10)
		pass

	def test_check_rows(self):
		table = table_test()
		count = table[1]
		self.assertEqual(256, count, 'incorrect number of rows in table')
	
	def test_check_unique_rows(self):
		ret = is_unique_row()
		self.assertEqual(True, ret, 'non-unique rows exist')

	def test_check_compress(self):
		ret = check_compress()
		self.assertEqual(True, ret, 'file did not compress')

	def test_compress_hurl(self):
		ret = check_hurl_compress()
		self.assertEqual(True, ret, 'hurl file did not compress')

	def test_check_decompress(self):
		ret = check_decompress()
		self.assertEqual(True, ret, 'file did not decompress')

	def test_decompress_hurl(self):
		ret = check_hurl_decompress()
		self.assertEqual(True, ret, 'hurl file did not compress')

	def test_exit_code(self):
		ret = check_exit_compress()
		self.assertEqual(255, ret, 'success') | self.assertEqual(0, ret, 'failure')

	def test_file_equality(self):
		ret = check_file_equality()
		self.assertEqual(True, ret, 'files not equal')

	def test_magic_number(self):
		ret = check_magic_number()
		self.assertEqual(True, ret, 'not HURL magic number')


	

def create_file():
	file_write = open("test_file.txt", "w")
	for elt in range(0, 256):
		file_write.write(chr(elt))
	file_write.close()
	return file_write

def create_other_file(filename):
	file_write = open(filename, "w")
	for elt in range(33, 126):
		file_write.write(chr(elt))
	file_write.close()
	return file_write

def table_test():
	test_file = create_file()
	file_write = open("table", "w")
	table_output = subprocess.Popen(["./rhuff", "-t", "test_file.txt"], stdout = subprocess.PIPE)
	output = table_output.communicate()[0]
	ln_count = output.count('\n')	
	
	return output, ln_count

def get_rows_from_table():
	sym_count = 0
	tab = table_test()
	table = tab[0]
	rows = table.splitlines()
	strcode = []
	for row in rows:		
		all_code = row.partition(" - ")
		code = all_code[2]
		code = code.split(" ")
		if len(code) == 3:
			fin_code = code[2]
		else:
			sym_count = sym_count + 1
		strcode.append(fin_code)	
	return strcode, sym_count
		
def is_unique_row():
	ret = get_rows_from_table()
	rows = ret[0]
	sym_count = ret[1]
	all_rows = len(rows)-sym_count	
	unique = set(rows)	
	unique_rows = len(unique)
	return (all_rows == unique_rows)

def check_compress():
	call(["./rhuff", "-c", "test_file.txt"])
	return os.path.exists("test_file.txt.hurl")
		

def check_decompress():
	call(["./rhuff", "-d", "test_file.txt.hurl"])
	return os.path.exists("test_file.txt")

def check_hurl_compress():
	call(["./rhuff", "-c", "test_file.txt"])
	call(["./rhuff", "-c", "test_file.txt.hurl"])
	return os.path.exists("test_file.txt.hurl.hurl")


def check_hurl_decompress():
	call(["rm", "-f", "test_file.txt.hurl"])
	call(["./rhuff", "-d", "test_file.txt.hurl.hurl"])
	return os.path.exists("test_file.txt.hurl")

def get_compressed_file_lines():	
	call(["./rhuff", "-c", "test_file.txt"])
	file_read = open("test_file.txt.hurl", "r") 
	file_lines = file_read.readlines()	
	return file_lines
	
def check_exit_compress():	
	f = create_other_file("compress_test.txt")
	outfile = open("out_compress_test.txt", "w")
	exit_code = subprocess.call(["./rhuff", "-c", "compress_test.txt"], stdout = outfile)
	outfile.close()
	return exit_code

def check_file_equality():
	tester = open("compare_tester.txt", "w")
	for elt in range(65, 122):
		tester.write(chr(elt))
	tester.close()
	shutil.copy('compare_tester.txt', 'original_tester.txt')
	call(["./rhuff", "-c", "compare_tester.txt"])
	call(["./rhuff", "-d", "compare_tester.txt.hurl"])
	return filecmp.cmp('compare_tester.txt', 'original_tester.txt')

def check_magic_number():
	call(["./rhuff", "-c", "test_file.txt"])
	with open('test_file.txt.hurl', 'rb') as hurl_file:
		magic = hurl_file.read(4).encode('hex')	
	#H U R L - 48 55 52 4C
	magic_num = "4855524C"
	return magic_num == magic
	
def large_compression(exp):
	size = pow(2, exp)
	file_write = open("large_test.txt", "w")
	for i in range(0, size):
		file_write.write('a')
	file_write.close()
	output = subprocess.Popen(["./rhuff", "-c", "large_test.txt"], stdout = subprocess.PIPE)
	data = output.communicate()[0]
	rc = output.returncode
	return rc
	
def main():
	#suite = unittest.TestLoader().loadTestsFromTestCase(TestCases)
	#unittest.TextTestRunner(verbosity=2).run(suite)
	large_compression(1)
	return 'end of test'

if __name__ == '__main__':
	main()
