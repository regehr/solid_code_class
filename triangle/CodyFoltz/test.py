#! /usr/bin/python
#basic idea for function syntax from Taylor J Stapleton
import subprocess

def test_is_ri():
	test_successful = True

        #Test 1
        output = subprocess.check_output(['./triangle' , '1' , '1' , '2' , '1', '1' , '2'])
        if(output != "isosceles right\n"):
                print("isosceles right: failed test 1\n")
		test_successful = False
	
        #Test 2
        output = subprocess.check_output(['./triangle' , '0' , '0' , '100', '0', '0', '100'])
	if(output != "isosceles right\n"):
		print("isosceles right: failed test 2\n")
		test_successful = False

        #Test3
        output = subprocess.check_output(['./triangle' , '0' , '0' , '5000', '0', '0', '5000'])
	if(output != "isosceles right\n"):
		print("isosceles right: failed test 3\n")
		test_successful = False

#Test4
        output = subprocess.check_output(['./triangle' , '5000' , '5000' , '5000', '0', '0', '5000'])
	if(output != "isosceles right\n"):
		print("isosceles right: failed test 4\n")
		test_successful = False


#Test5
        output = subprocess.check_output(['./triangle' , '12345678' , '12345678' , '12345678', '0', '0', '12345678'])
	if(output != "isosceles right\n"):
		print("isosceles right: failed test 5\n")
		test_successful = False



	return test_successful

def main():
       	success = test_is_ri()

	if (success): 
		print("All Tests Passed!!!!\n")

if __name__ == '__main__':
        main()
