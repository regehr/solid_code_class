#!/bin/sh

make > /dev/null || { echo "couldn't make huff" && exit ; }
cp ./huff ./test/huff
cd ./test
echo 'Generating first random test file...'
head -c 1048576 < /dev/urandom > rand1
echo 'Generating second random test file...'
head -c 10485760 < /dev/urandom > rand2
echo 'Generating third random test file...'
head -c 104857600 < /dev/urandom > rand3
python3 test.py
rm -f ./huff ./rand1 ./rand2 ./rand3
