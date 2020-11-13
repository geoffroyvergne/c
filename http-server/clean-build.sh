#!/bin/sh

# Linux
#export CC=/usr/bin/clang-9
#export CXX=/usr/bin/clang++-9

# Freebsd
#export CC=/usr/local/bin/clang90
#export CXX=/usr/local/bin/clang++90

rm -Rf build/

cmake -DCMAKE_C_FLAGS="-pthread" . -B build/
#cmake -DCMAKE_C_FLAGS="-pthread -static" . -B build/

cmake --build build/
