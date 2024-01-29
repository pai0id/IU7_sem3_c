#!/bin/bash

in_file=$1
prog="./app.exe"

if ! $prog < "$in_file" > ./out/tmp ; then
    exit 0
else
    exit 1
fi
