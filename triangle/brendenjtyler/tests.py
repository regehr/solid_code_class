from subprocess import call
from subprocess import check_output

#create a dictionary using the outputs of the program as keys
outputs = {check_output(["./triangle", "1", "0", "3", "0", "1", "4"]):0, 
           check_output(["./triangle", "1", "1", "2", "2", "2", "3"]):0,
           check_output(["./triangle", "1", "1", "4", "1", "2", "6"]):0,
           check_output(["./triangle", "1", "1", "3", "1", "2", "2"]):0,
           check_output(["./triangle", "1", "1", "11", "1", "6", "3"]):0,
           check_output(["./triangle", "1", "1", "3", "1", "2", "6"]):0,
           check_output(["./triangle", "1", "1", "2", "2", "3", "3"]):0}

#test to make sure we can print each result
#scalene right
call(["./triangle", "1", "0", "3", "0", "1", "4"])

#scalene obtuse
call(["./triangle", "1", "1", "2", "2", "2", "3"])

#scalene acute
call(["./triangle", "1", "1", "4", "1", "2", "6"])

#isosceles right
call(["./triangle", "1", "1", "3", "1", "2", "2"])

#isosceles obtuse
call(["./triangle", "1", "1", "11", "1", "6", "3"])

#isosceles acute
call(["./triangle", "1", "1", "3", "1", "2", "6"])

#not a triangle
call(["./triangle", "1", "1", "2", "2", "3", "3"])

#test everything from (0,0) (0,0) (0,0) to (3,3) (3,3) (3,3)
for first in range(0, 4):
    for second in range(0, 4):
        for third in range(0, 4):
            for fourth in range(0, 4):
                for fifth in range(0, 4):
                    for sixth in range(0, 4):
                        #get the result of the call and decode it into a string
                        result = check_output(["./triangle", str(first), str(second), str(third), str(fourth), str(fifth), str(sixth)])
                        occurences = outputs[result]
                        occurences += 1
                        outputs[result] = occurences

for key in outputs.keys():
    print(key.decode("utf-8") + str(outputs[key]))
