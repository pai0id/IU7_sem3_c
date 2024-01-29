#!/bin/bash

in_file=$1
out_file=$2
prog="./app.exe"

$prog < "$in_file" > ./out/tmp

if ./func_tests/scripts/comparator.sh ./out/tmp "$out_file" ; then
    exit 0
else
    exit 1
fi
