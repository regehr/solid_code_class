#!/usr/bin/env bash

export IFS=$'\n'
for dir in `ls -d ../*/`
do
    echo "=================================================="
    echo "$dir"
    echo "=================================================="
    (cd "$dir"; ../clukey/test.py)
    echo
done
