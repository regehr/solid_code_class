#!/bin/bash

export IFS=$'\n'

cd ..
./compile_all.pl
for dir in $(ls -l | awk '/^d/ {printf("%s\n", substr($0, 44))}'); do
  if [[ -e "${dir}/triangle" ]]; then
    printf '%s:\t%s\n' "${dir}" "$(cd "${dir}"; ../oscarmarshall/test.sh -q)"
  fi
done
