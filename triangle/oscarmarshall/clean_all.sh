#!/usr/bin/env bash

export IFS=$'\n'

cd ..
for dir in $(ls -l | awk '/^d/ {printf("%s\n", substr($0, 44))}'); do
  (cd "${dir}"; make clean)
done
