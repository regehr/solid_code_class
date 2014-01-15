'''
Created on Jan 10, 2014

@author: Tom
'''
import subprocess
import math

def isoPartition():
	#Test output of scaling isosceles right
	starty1 = 1
	startx2 = 1
	for x in range(1, 10) :
		output = subprocess.check_output(['./triangle', '0', '0', '0', str(starty1*math.pow(2,x)), str(startx2*math.pow(2,x)), '0'])
		if(output != 'isosceles right\n') :
			print("Failed isosceles right test. Coords: (0,0) (0,"+str(starty1*math.pow(2,x))+") ("+str(startx2*math.pow(2,x))+",0)")
			print("Triangle output: " + output)
			
	#Test output of scaling isosceles acute
	starty1 = 2
	for x in range(1, 10) :
		output = subprocess.check_output(['./triangle', '0', '0', '1', str(starty1*math.pow(2,x)), '2', '0'])
		if(output != 'isosceles acute\n') :
			print("Failed isosceles acute test. Coords: (0,0) (1,"+str(starty1*math.pow(2,x))+") (2,0)")
			print("Triangle output: " + output)
		
	#Test output of scaling isosceles obtuse
	startx2 = 2
	for x in range(1, 10) :
		output = subprocess.check_output(['./triangle', '0', '0', str((startx2*math.pow(2,x))/2), '1', str(startx2*math.pow(2,x)), '0'])
		if(output != 'isosceles obtuse\n') :
			print("Failed isosceles obtuse test. Coords: (0,0) ("+str((startx2*math.pow(2,x))/2)+",1) ("+str(startx2*math.pow(2,x))+",0)")
			print("Triangle output: " + output)
			
def scaPartition():
	#Test output of scaling scalene right
	startx2 = 1
	for x in range(1, 10) :
		output = subprocess.check_output(['./triangle', '0', '0', '0', '1', str(startx2*math.pow(2,x)), '0'])
		if(output != 'scalene right\n') :
			print("Failed scalene right test. Coords: (0,0) (0,1) ("+str(startx2*math.pow(2,x))+",0)")
			print("Triangle output: " + output)
			
	#Test output of scaling scalene acute
	startx2 = 2
	for x in range(1, 10) :
		output = subprocess.check_output(['./triangle', '0', '0', str(((startx2*math.pow(2,x))/2)-1), str(startx2*math.pow(2,x)), str(startx2*math.pow(2,x)), '0'])
		if(output != 'scalene acute\n') :
			print("Failed scalene acute test. Coords: (0,0) ("+str(((startx2*math.pow(2,x))/2)-1)+","+str(startx2*math.pow(2,x))+") ("+str(startx2*math.pow(2,x))+",0)")
			print("Triangle output: " + output)
			
	#Test output of scaling scalene obtuse
	startx2 = 2
	for x in range(1, 10) :
		output = subprocess.check_output(['./triangle', '0', '0', '1', '1', str(startx2*math.pow(2,x)), '0'])
		if(output != 'scalene obtuse\n') :
			print("Failed scalene obtuse test. Coords: (0,0) (1,1) ("+str(startx2*math.pow(2,x))+",0)")
			print("Triangle output: " + output)

def natPartition():
	#Test output of scaling NAT (line)
	startx1 = 1
	startx2 = 2
	for x in range(1,10) :
		output = subprocess.check_output(['./triangle', '0', '0', str(startx1*math.pow(2,x)), str(startx1*math.pow(2,x)), str(startx2*math.pow(2,x)), str(startx2*math.pow(2,x))])
		if(output != "not a triangle\n") :
			print("Failed not a triangle test. Coords: (0,0) ("+str(startx1*math.pow(2,x))+","+str(startx1*math.pow(2,x))+") ("+str(startx1*math.pow(2,x))+","+str(startx1*math.pow(2,x))+")")
			print("Triangle output: " + output)
			
	#Test output of NAT (dot)        
   	output = subprocess.check_output(['./triangle', '0', '0', '0', '0', '0', '0'])
    	if(output != "not a triangle\n") :
        	print("Failed not a triangle test. Coords: (0,0) (0,0) (0,0)")
    		print("Triangle output: " + output)

def main():
	isoPartition()
	scaPartition()
	natPartition()

if __name__ == '__main__':
    	main()
