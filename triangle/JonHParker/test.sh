#!/bin/bash

#  Jon Parker
#
#  This script will run some tests against triangle.


echo "#############################################"
echo "#########                          ##########"
echo "#########     Testing Triangle     ##########"
echo "#########                          ##########"
echo "#############################################"

./triangle 0 0 10 0 6 1 > results.txt
./triangle 0 0 10 0 5 1 >> results.txt
./triangle 0 0 10 0 5 40 >> results.txt
./triangle 0 0 10 0 6 40 >> results.txt
./triangle 0 0 0 5 5 0 >> results.txt
./triangle 0 0 0 5 6 0 >> results.txt
./triangle 0 0 0 0 6 0 >> results.txt
./triangle 0 0 1 4 2 8 >> results.txt
./triangle 2147483647 2147483647 2147483647 2147483647 2147483647 2147483647 >> results.txt
./triangle 2147483647 0 0 0 0 0 >> results.txt
./triangle 0 2147483647 0 0 0 0 >> results.txt
./triangle 2147483647 2147483647 2147483646 2147483647 2147483647 2147483646 >> results.txt
./triangle 2147483647 2147483647 2147483646 2147483646 2147483645 2147483645 >> results.txt
./triangle 2147483645 2147483645 2147483646 2147483646 2147483647 2147483647 >> results.txt
./triangle 2147483647 2147483647 0 2147483647 2147483647 0 >> results.txt
./triangle 2147483647 2147483647 1073741822 1073741822 0 0 >> results.txt
./triangle 1073741822 1073741822 1073741832 1073741822 1073741828 1073741823 >> results.txt

echo "scalene obtuse
isosceles obtuse
isosceles acute
scalene acute
isosceles right
scalene right
not a triangle
not a triangle
not a triangle
not a triangle
not a triangle
isosceles right
not a triangle
not a triangle
isosceles right
not a triangle
scalene obtuse" > oracle.txt;

cat results.txt

if diff results.txt oracle.txt > /dev/null ; then
	echo "Pass"
else
	echo "Fail"
fi

echo "#############################################"
echo "#########                          ##########"
echo "#########     Testing Complete     ##########"
echo "#########                          ##########"
echo "#############################################"

