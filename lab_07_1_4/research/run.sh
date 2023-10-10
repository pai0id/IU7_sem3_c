#!/bin/bash

# Сборка приложений для каждого размера массива, для каждой программы

rm -f -r graphs tables
mkdir -p apps graphs tables

sizes="1 10 50 500 1000 1500 2000 2500 3000 3500 4000 4500 5000 5500 6000 6500 7000 7500 8000 8500 9000 9500 10000"

for i in ./*.c ; do
    for j in $sizes ; do
        cd apps || exit
        app="${i%.c}_$(printf "%05d" "$j").exe"
        gcc -Wall -I ../../inc -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -o $app "../$i" ../../src/mysort.c -lrt -Dn="$j" -lm
        $app
        cd ..
    done
done

echo "DONE"
