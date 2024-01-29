#!/bin/bash

in_file=$1
out_file=$2
if [ "$3" == "--valgrind" ]; then
    prog="valgrind --leak-check=yes -q ./app.exe"
else
    prog="./app.exe"
fi

read -r args < "$in_file"

IFS=' ' read -r -a args <<< "$args"

$prog "${args[@]}"

if ./func_tests/scripts/comparator.sh ./out/tmp "$out_file" ; then
    exit 0
else
    exit 1
fi
