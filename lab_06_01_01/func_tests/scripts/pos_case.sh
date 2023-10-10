#!/bin/bash

in_file=$1
out_file=$2
prog="./app.exe"

read -r args < "$in_file"

IFS=' ' read -r -a args <<< "$args"

$prog "${args[@]}" > tmp

if ./func_tests/scripts/comparator.sh tmp "$out_file" ; then
    exit 0
else
    exit 1
fi
