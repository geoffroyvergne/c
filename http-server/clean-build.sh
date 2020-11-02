#!/bin/sh

rm -Rf build/

mkdir build
conan install . -if build/ 

cmake . -B build/
#cmake -DCMAKE_C_FLAGS="-pthread -static" . -B build/

cmake --build build/
