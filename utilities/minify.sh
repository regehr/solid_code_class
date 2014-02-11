#!/bin/sh

# replace spaces with tabs to save on disk space for source code
sed -e 's/  /	/g' fuzz_file.c > fuzz_file.min.c
