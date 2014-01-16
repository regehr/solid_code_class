#!/usr/bin/env bash

export IFS=$'\n'
for dir in `ls -d ../*/`
do
    echo "$dir"
    (cd "$dir"; ../clukey/test.py)
done