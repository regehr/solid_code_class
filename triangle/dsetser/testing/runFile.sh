#!/bin/bash

IFS=$'\n' read -d '' -r -a input < $1

cat $1 | while read LINE ; do
	echo -e `../triangle $LINE`
done

