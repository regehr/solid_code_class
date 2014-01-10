#!/bin/bash

testing/runFile.sh testing/testInputs.txt > testing/output.txt

if diff testing/output.txt testing/expected.txt > /dev/null ; then
	echo "All tests passed"
else
	echo "At least one test failed"
fi
