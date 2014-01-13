import subprocess

def isoscelesTest():
	
	output = subprocess.check_output(['./triangle', '0', '0', '0', '1', '1', '0'])
	
	if(output != "isosceles right\n"):
		return "isosceles right fail"
	
	output = subprocess.check_output(['./triangle', '0', '0', '2', '1', '0', '2'])
	
	if(output != "isosceles acute\n"):
		return "isosceles acute fail"
		
	output = subprocess.check_output(['./triangle', '0', '0', '2', '1', '4', '0'])
	
	if(output != "isosceles obtuse\n"):
		return "isosceles obtuse fail"
		
	return "pass"


def scaleneTest():
	output = subprocess.check_output(['./triangle', '0', '0', '0', '2', '1', '0'])
	
	if(output != "scalene right\n"):
		return "scalene right fail"
		
	output = subprocess.check_output(['./triangle', '0', '0', '2', '2', '0', '3'])
	
	if(output != "scalene acute\n"):
		return "scalene acute fail"
		
	output = subprocess.check_output(['./triangle', '0', '0', '1', '1', '0', '3'])
	
	if(output != "scalene obtuse\n"):
		return "scalene obtuse fail"
		
	return "pass"
		
		
def badTriangleTest():
	output = subprocess.check_output(['./triangle', '0', '0', '0', '0', '0', '0'])
	
	if(output != "not a triangle\n"):
		return "same point test fail"
		
	output = subprocess.check_output(['./triangle', '0', '0', '1', '1', '2', '2'])
	
	if(output != "not a triangle\n"):
		return "collinear test fail"
				
	output = subprocess.check_output(['./triangle', '0'])
	
	if(output != "not a triangle\n"):
		return "input test fail"	
		
	return "pass"

def main():
	
	print("Isosceles Test: " + isoscelesTest())
	print("Scalene Test: " + scaleneTest())
	print("Bad Triangle Test: " + badTriangleTest())
	
	
if __name__ == '__main__':
	main()