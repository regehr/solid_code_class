'''
Created on Jan 10, 2014

@author: Tom

Used Taylor J Stapleton's test.py as a basis.
'''
import subprocess

def isoPartition():
    result = ""
    
    output = subprocess.check_output(['./triangle', '0', '0', '6', '0', '3', '10'])
    if(output != "isoscelese acute\n") :
        print("Expected: iscoscelese acute")
    	print("  Actual: " + output)
        result += "Acute "
        
    output = subprocess.check_output(['./triangle', '0', '0', '5', '0', '0', '5'])
    if(output != "isoscelese right\n") :
        print("Expected: iscoscelese right")
    	print("  Actual: " + output)
        result += "Right "
        
    output = subprocess.check_output(['./triangle', '0', '0', '12', '0', '6', '2'])
    if(output != "isoscelese obtuse\n") :
    	print("Expected: iscoscelese obtuse")
    	print("  Actual: " + output)
        result += "Obtuse "
        
    return result

def scaPartition():
    result = ""
    
    output = subprocess.check_output(['./triangle', '0', '0', '3', '3', '4', '0'])
    if(output != "scalene acute\n") :
        print("Expected: scalene acute")
    	print("  Actual: " + output)
        result += "Acute "
        
    output = subprocess.check_output(['./triangle', '0', '0', '0', '1', '5', '0'])
    if(output != "scalene right\n") :
        print("Expected: scalene right")
    	print("  Actual: " + output)
        result += "Right "
        
    output = subprocess.check_output(['./triangle', '0', '0', '12', '1', '3', '0'])
    if(output != "scalene obtuse\n") :
        print("Expected: scalene obtuse")
    	print("  Actual: " + output)
        result += "Obtuse "
        
    return result

def natPartition():
    result = ""
    
    output = subprocess.check_output(['./triangle', '0', '0', '1', '0', '2', '0'])
    if(output != "not a triangle\n") :
        print("Expected: not a triangle")
    	print("  Actual: " + output)
        result += "Line "
        
    output = subprocess.check_output(['./triangle', '0', '0', '0', '0', '0', '0'])
    if(output != "not a triangle\n") :
        print("Expected: not a triangle")
    	print("  Actual: " + output)
        result += "Dot "

    return result

def main():
    testResult = isoPartition()
    if(testResult != "") :
        print("Isoscelese partition failed, case: " + testResult)
        
    testResult = scaPartition()
    if(testResult != "") :
        print("Scalene partition failed, case: " + testResult)
        
    testResult = natPartition()
    if(testResult != "") :
        print("NAT partition failed, case: " + testResult)

if __name__ == '__main__':
    main()
