#!/bin/sh

#export CC = /usr/bin/clang-9
#export CXX = /usr/bin/clan++-9

rm -Rf build/

#cmake . -B build/
cmake -DCMAKE_C_FLAGS="-pthread" . -B build/
cmake --build build/
