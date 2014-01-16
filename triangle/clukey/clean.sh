#!/usr/bin/env bash

export IFS=$'\n'
for dir in `ls -d ../*/`
do 
    (cd "$dir"; make clean)
done