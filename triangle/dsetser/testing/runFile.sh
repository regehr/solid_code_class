#!/bin/bash

IFS=$'\n' read -d '' -r -a input < $1

cat $1 | while read LINE ; do
	if [[ $LINE != //* ]]
	then
		echo -e `./triangle $LINE`
	fi
done

