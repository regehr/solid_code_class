Triangle Analyzer README
by Daniel Setser

"make" will build the analyzer
"make clean" will clean all generated files
"make test" will run the current tests
"make coverage" will generate code coverage information from current tests

In order to add or edit tests you need to edit two files:
	testing/testInputs.txt: 
		Each line in this file represents the parameters to test a triangle
		(excluding lines starting with "//")

	testing/expected.txt:
		Each line corresponds to the same line in testInputs, and is the output
		expected for each input. So if the first line of testInputs.txt is 
		"0 0 0 0 0 0", expected.txt's first line should be "not a triangle".

If any test fails, the test will print "At least one test failed". You can 
then use a tool like diff in order to find the differences in 
testing/expected.txt and testing/output.txt to see which test failed.

