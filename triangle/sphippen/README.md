Triangle Analyzer (Spencer Phippen)
===================================

### DEPENDENCIES
This code has a dependency on the GMP library.
The system installation of GMP on CADE is messed up, so I created a proper
installation of GMP in my home directory.

If you have Homebrew on OS X: "brew install gmp". (I did this on my system).

### COMPILATION
##### CADE
Run "make" in this directory; I added the necessary flags.

##### Other
Remove `$(CADE_FLAGS)` from the `COMMON_FLAGS = ...` line in `Makefile` and
make sure that your installation of GMP is set up right, adding search paths,
etc. to the `COMMON_FLAGS = ...` line as needed. Then run "make" in this
directory.

### TESTING
You'll need to properly set up compilation before testing. Once again, on CADE,
no setup is needed.

Run "make test" in this directory. The test script will print a message saying
either:

* All tests passed, or
* At least one failed, and give you a filename where details are written
