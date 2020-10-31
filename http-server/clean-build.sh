#!/bin/sh

rm -Rf build/

mkdir build
conan install . -if build/ 

cmake . -B build/
cmake --build build/
