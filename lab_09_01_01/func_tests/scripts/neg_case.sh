#!/bin/bash

in_file=$1
prog="./app.exe"

read -r args < "$in_file"

IFS=' ' read -r -a args <<< "$args"

if ! $prog "${args[@]}" > tmp ; then
    exit 0
else
    exit 1
fi
