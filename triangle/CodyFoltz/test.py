#! /usr/bin/python
#basic idea from Taylor J Stapleton
import subprocess

def test_is_ri():
	test_successful = True
        output = subprocess.check_output(['./triangle' , '1' , '1' , '2' , '1', '1' , '2'])
        if(output != "isosceles right\n"):
                print("isosceles right: failed test 1\n")
		test_successful = False
	output = subprocess.check_output(['./triangle' , '0' , '0' , '100', '0', '0' '100'])
	if(output != "isosceles right\n"):
		print("isosceles right: failed test 2\n")
		test_sucessful = False
	return test_successful

def main():
       	success = test_is_ri()

	if(success)
		print("All Tests Passed!!!!\n")

if __name__ == '__main__':
        main()
