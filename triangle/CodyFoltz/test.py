#! /usr/bin/python
#basic idea for function syntax from Taylor J Stapleton
import subprocess


def get_points(input):
        point1 = "(" + input[1] +"," + input[2]+")"
        point2 =  "(" + input[3] +"," + input[4]+")"
        point3 =  "(" + input[5] +"," + input[6]+")"
        points = point1 + " " + point2 + " " + point3
        return points

def print_test_failed(points, expected, received):
        expected = expected.replace("\n","")
        received = received.replace("\n","")
        print("~~~~~~~Test Failed~~~~~~~")
        print("Input: " + points)
        print("Expected: " + expected)
        print("Received: " + received)
        print("~~~~~~~~~~~~~~~~~~~~~~~~~")

def test_is_ri():
	test_failed = False
        expected = "isosceles right\n"
        input = ['./triangle' , '1' , '1' , '2' , '1', '1' , '2']
        points = "(1,1) (2,1) (1,2)"

#Test 1
        output = subprocess.check_output(input)
        if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True
	
#Test 2
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '0' , '0' , '100' , '0', '0' , '100']
        output = subprocess.check_output(input)
	if(output != expected):
		print_test_failed(get_points(input), expected, output)
		test_failed = True

#Test3
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '0' , '0' , '5000', '0', '0', '5000']
        output = subprocess.check_output(input)
	if(output != expected):
		print_test_failed(get_points(input), expected, output)
		test_failed = True

#Test4
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '5000' , '5000' , '5000', '0', '0', '5000']
        output = subprocess.check_output(input)
	if(output != expected):
		print_test_failed(get_points(input), expected, output)
		test_failed = True

#Test5
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '12345678' , '12345678' , '12345678', '0', '0', '12345678']
        output = subprocess.check_output(input)
	if(output != expected):
		print_test_failed(get_points(input), expected, output)
		test_failed = True

#Test6
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '0' , '0' , '0', '2147483647', '2147483647', '0']
        output = subprocess.check_output(input)
	if(output != expected):
		print_test_failed(get_points(input), expected, output)
		test_failed = True
#Test7
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '0' , '2147483647' , '2147483647', '2147483647', '2147483647', '0']
        output = subprocess.check_output(input)
	if(output != expected):
		print_test_failed(get_points(input), expected, output)
		test_failed = True

#Test8
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '0' , '0' , '0', '2147483647', '2147483647', '2147483647']
        output = subprocess.check_output(input)
	if(output != expected):
		print_test_failed(get_points(input), expected, output)
		test_failed = True

#Test9
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '0' , '0' , '2147483647', '0', '2147483647', '2147483647']
        output = subprocess.check_output(input)
	if(output != expected):
		print_test_failed(get_points(input), expected, output)
		test_failed = True

	return test_failed





def test_is_ob():
	test_failed = False
        expected = "isosceles obtuse\n"
        input = ['./triangle' , '1' , '1' , '3' , '0', '0' , '3']
        points = "(1,1) (2,1) (1,2)"

#Test 1
        output = subprocess.check_output(input)
        if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True
	
#Test 2
        input = ['./triangle' , '1' , '1' , '100', '0', '0', '100']
        points = "(1,1) (100,0) (1,2)"
        output = subprocess.check_output(input)
	if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True

#Test3
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '1' , '1' , '5000', '0', '0', '5000']
        output = subprocess.check_output(input)
	if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True

#Test4
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '2501' , '2501' , '5000', '0', '0', '5000']
        output = subprocess.check_output(input)
	if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True


#Test5
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '2345679' , '2345679' , '12345678', '0', '0', '12345678']
        output = subprocess.check_output(input)
	if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True

#Test6
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '1' , '1' , '0', '2147483647', '2147483647', '0']
        output = subprocess.check_output(input)
	if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True

#Test7
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '2147483646' , '2147483646' , '0', '2147483647', '2147483647', '0']
        output = subprocess.check_output(input)
	if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True

#Test8
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '0' , '5' , '5', '0', '1', '1']
        output = subprocess.check_output(input)
	if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True


	return test_failed

def sc_ri():
        test_failed = False
        expected = "scalene right\n"
        

#Test 1
        input = ['./triangle' , '1', '2147483647', '0', '2147483647', '0', '0']
        points = "(1,2147483647) (0,2147483647) (0,0)"
        output = subprocess.check_output(input)
	if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True

#Test 2
        input = ['./triangle' , '0' , '0' , '0', '1', '2147483647', '0']
        points = "(1,2147483647) (0,2147483647) (0,0)"
        output = subprocess.check_output(input)
	if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True

#Test 3
        input = ['./triangle' , '0' , '0' , '0', '2147483647', '2147483646', '0']
        points = "(1,2147483647) (0,2147483647) (0,0)"
        output = subprocess.check_output(input)
	if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True

#Test 4
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '0' , '2147483647' , '2147483647', '2147483647', '2147483647', '2147483646']
        output = subprocess.check_output(input)
	if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True

        return test_failed

def sc_ac():

        test_failed = False
        expected = "scalene acute\n"

#Test 1
        input = ['./triangle' , '0', '0', '1', '2147483647', '2147483647', '1147483647']
        points = "(1,2147483647) (0,2147483647) (0,0)"
        output = subprocess.check_output(input)
	if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True

        return test_failed

def sc_ob():

        test_failed = False
        expected = "scalene obtuse\n"
        

#Test 1
        points = "(0,0) (2,2147483647) (0,0)"
        input = ['./triangle' , '0', '0', '2', '2147483647', '100', '100']
        output = subprocess.check_output(input)
	if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True

        return test_failed

def is_ac():

        test_failed = False
        expected = "scalene right\n"
        

#Test 1
        points = "(1,2147483647) (0,2147483647) (0,0)"
        input = ['./triangle' , '0', '0', '20', '0', '10', '10']
        output = subprocess.check_output(input)
	if(output != expected):
                print_test_failed(get_points(input), expected, output)
		test_failed = True

        return test_failed

def main():
       	test_failed = test_is_ri()
        test_failed = test_failed or test_is_ob()
        test_failed = sc_ri()

	if (not test_failed): 
		print("All Tests Passed!!!!\n")

if __name__ == '__main__':
        main()
