#! /usr/bin/python

import subprocess

def test_is_ri():
        output = subprocess.check_output(['./triangle' , '1' , '1' , '2' , '1', '1' , '2'])
        if(output != "isosceles right\n"):
                print("isosceles right: failed test 1\n")

def main():
       	test_is_ri()

if __name__ == '__main__':
        main()
