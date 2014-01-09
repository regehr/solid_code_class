#!/bin/bash

cd ..
make
cd testing

./runFile.sh testInputs.txt > output.txt

if diff output.txt expected.txt > /dev/null ; then
	echo "All tests passed"
else
	echo "At least one test failed"
fi
