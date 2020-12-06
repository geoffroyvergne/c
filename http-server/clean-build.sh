#!/bin/sh

rm -Rf build/

./configure.sh

#mkdir build
#conan install . -if build/ 
#conan install --build=missing . -if build/ && \
#cmake . -B build/
#cmake -DCMAKE_CXX_FLAGS="-static" . -B build/
#cmake . -DCMAKE_CXX_FLAGS="-pthread" -DCMAKE_CXX_COMPILER=/usr/bin/clang++-9 -B build/
#cmake . -DCMAKE_CXX_FLAGS="-pthread -Wno-c++11-narrowing -static" -B build/ && \
#cmake . -DCMAKE_CXX_FLAGS="-pthread" -DCMAKE_CXX_COMPILER=/usr/local/bin/clang++10 -B build/

cmake --build build/
