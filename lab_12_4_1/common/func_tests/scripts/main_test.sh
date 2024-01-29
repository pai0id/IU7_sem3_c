#!/bin/bash

BLUE=$'\e[1;34m'
GREEN=$'\e[1;32m'
RED=$'\e[1;31m'
NC=$'\e[1;0m'
n_err=0

echo "$BLUE build debug: $NC"
echo
make -s debug
if ./func_tests/scripts/func_tests.sh; then
    echo "$GREEN GOOD $NC"
else
    echo "$RED BAD $NC"
    n_err=$((n_err+1))
fi
make -s clean
echo
echo "$BLUE valgrind: $NC"
echo
make -s valgrind
make -s clean
echo
echo "$BLUE build /w address sanitizer: $NC"
echo
make -s debug_asan
if ./func_tests/scripts/func_tests.sh; then
    echo "$GREEN GOOD $NC"
else
    echo "$RED BAD $NC"
    n_err=$((n_err+1))
fi
make -s clean
echo
echo "$BLUE build /w memory sanitizer: $NC"
echo
make -s debug_msan
if ./func_tests/scripts/func_tests.sh; then
    echo "$GREEN GOOD $NC"
else
    echo "$RED BAD $NC"
    n_err=$((n_err+1))
fi
make -s clean
echo
echo "$BLUE build /w undefined behavior sanitizer: $NC"
echo
make -s debug_ubsan
if ./func_tests/scripts/func_tests.sh; then
    echo "$GREEN GOOD $NC"
else
    echo "$RED BAD $NC"
    n_err=$((n_err+1))
fi
make -s clean
echo
echo "$BLUE build /w gcov: $NC"
make -s debug_gcov
./func_tests/scripts/func_tests.sh -s
echo
echo "Result:"
echo
for i in ./out/*.gcno ; do
    gcov "$i"
    echo
done
mv ./*.gcov ./out
make -s clean
echo
if [ $n_err != 0 ]; then
    echo " $RED ERROR OCCURED $NC"
else
    echo "$GREEN ALL GOOD $NC"
fi

exit $n_err
