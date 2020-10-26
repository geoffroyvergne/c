#!/bin/sh

rm -Rf build/

cmake . -B build/
cmake --build build/
