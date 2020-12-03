#!/bin/sh

rm -Rf build/
#cmake  -D CMAKE_C_COMPILER=/usr/local/Cellar/llvm/11.0.0/bin/clang . -B build/
cmake . -B build/

cmake --build build/