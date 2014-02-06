#!/bin/sh

make > /dev/null || { echo "couldn't make huff" && exit ; }
cp ./huff ./test/huff
cd ./test
python3 test.py
rm ./huff
