#!/bin/bash

file1=$1
file2=$2
verb=$3


if [ -z "$file1" ] || [ -z "$file2" ] || [ ! -f "$file1" ] || [ ! -f "$file2"  ]; then
	if [[ $verb == "-v" ]]; then
		echo "Please enter correct file names"
	fi
	exit 2
elif [ ! -r "$file1" ] || [ ! -r "$file2"  ]; then
	if [[ $verb == "-v" ]]; then
		echo "Permission error"
	fi
	exit 3
fi

nums1=$(grep -owE "[-]?[0-9]+(\.[0-9]+)?" "$file1")
nums2=$(grep -owE "[-]?[0-9]+(\.[0-9]+)?" "$file2")

if [[ "$nums1" == "$nums2" ]]; then
	if [[ $verb == "-v" ]]; then
                echo "files match"
        fi
	exit 0
else
	if [[ $verb == "-v" ]]; then
                echo "files do not  match"
        fi
	exit 1
fi
