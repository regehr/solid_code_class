from subprocess import call

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
