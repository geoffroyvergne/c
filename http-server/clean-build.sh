#!/bin/sh

./configure.sh

rm -Rf build/

cmake -DCMAKE_C_FLAGS="-pthread" . -B build/
#cmake -DCMAKE_C_FLAGS="-pthread -static" . -B build/

cmake --build build/
