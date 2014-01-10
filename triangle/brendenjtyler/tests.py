from subprocess import call

#right
call(["./triangle", "1", "1", "3", "1", "2", "2"])

#scalene obtuse
call(["./triangle", "1", "1", "2", "2", "2", "3"])

#scalene acute
call(["./triangle", "1", "1", "4", "1", "2", "6"])

#isosceles obtuse
call(["./triangle", "1", "1", "11", "1", "6", "3"])

#isosceles acute
call(["./triangle", "1", "1", "3", "1", "2", "6"])

#not a triangle
call(["./triangle", "1", "1", "2", "2", "3", "3"])
