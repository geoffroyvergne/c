#!/bin/sh

./configure.sh

rm -Rf build/

#cmake . -B build/
cmake -DCMAKE_C_FLAGS="-pthread" . -B build/
cmake --build build/
