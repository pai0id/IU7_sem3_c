#!/bin/bash

in_file=$1
if [ "$2" == "--valgrind" ]; then
    prog="valgrind --leak-check=yes -q ./app.exe"
else
    prog="./app.exe"
fi

read -r args < "$in_file"

IFS=' ' read -r -a args <<< "$args"

if ! $prog "${args[@]}" ; then
    exit 0
else
    exit 1
fi
