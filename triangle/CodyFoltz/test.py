#! /usr/bin/python
#basic idea for function syntax from Taylor J Stapleton
import subprocess

def test_is_ri():
	test_failed = False

        #Test 1
        output = subprocess.check_output(['./triangle' , '1' , '1' , '2' , '1', '1' , '2'])
        if(output != "isosceles right\n"):
                print("isosceles right: failed test 1\n")
		test_failed = True
	
        #Test 2
        output = subprocess.check_output(['./triangle' , '0' , '0' , '100', '0', '0', '100'])
	if(output != "isosceles right\n"):
		print("isosceles right: failed  '0 0 100 0 0 100' \n")
		test_failed = True

        #Test3
        output = subprocess.check_output(['./triangle' , '0' , '0' , '5000', '0', '0', '5000'])
	if(output != "isosceles right\n"):
		print("isosceles right: failed test 3\n")
		test_failed = True

#Test4
        output = subprocess.check_output(['./triangle' , '5000' , '5000' , '5000', '0', '0', '5000'])
	if(output != "isosceles right\n"):
		print("isosceles right: failed test 4\n")
		test_failed = True


#Test5
        output = subprocess.check_output(['./triangle' , '12345678' , '12345678' , '12345678', '0', '0', '12345678'])
	if(output != "isosceles right\n"):
		print("isosceles right: failed test 5\n")
		test_failed = True



	return test_failed


def test_is_ob():
	test_failed = False

#Test 1
        output = subprocess.check_output(['./triangle' , '1' , '1' , '3' , '0', '0' , '3'])
        if(output != "isosceles obtuse\n"):
                print("isosceles obtuse: failed test 1\n")
		test_failed = True
	
#Test 2
        output = subprocess.check_output(['./triangle' , '1' , '1' , '100', '0', '0', '100'])
	if(output != "isosceles obtuse\n"):
                print("isosceles obtuse: failed test 2\n")
		test_failed = True

#Test3
        output = subprocess.check_output(['./triangle' , '1' , '1' , '5000', '0', '0', '5000'])
	if(output != "isosceles obtuse\n"):
                print("isosceles obtuse: failed test 3\n")
		test_failed = True

#Test4
        output = subprocess.check_output(['./triangle' , '2501' , '2501' , '5000', '0', '0', '5000'])
	if(output != "isosceles obtuse\n"):
                print("isosceles obtuse: failed test 4\n")
		test_failed = True


#Test5
        output = subprocess.check_output(['./triangle' , '2345679' , '2345679' , '12345678', '0', '0', '12345678'])
	if(output != "isosceles obtuse\n"):
                print("isosceles obtuse: failed test 5\n")
		test_failed = True



	return test_failed

def sc_ri():
        output = subprocess.check_output(['./triangle' , '1', '2147483647', '0', '2147483647', '0', '0'])
	if(output != "scalene right\n"):
                print("isosceles obtuse: failed test 5\n")
		test_failed = True
        return test_failed

def main():
       	test_failed = test_is_ri()
        test_failed = test_failed or test_is_ob()
        test_failed = sc_ri()

	if ( not test_failed): 
		print("All Tests Passed!!!!\n")

if __name__ == '__main__':
        main()
