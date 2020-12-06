#!/bin/sh

# Linux
if [ "$(uname)" = "Linux" ]; then
echo "Linux detected"
export CC=/usr/bin/clang-9
export CXX=/usr/bin/clang++-9
fi

# Freebsd
if [ "$(uname)" = "FreeBSD" ];  then 
echo "FreeBsd detected"
export CC=/usr/local/bin/clang90
export CXX=/usr/local/bin/clang++90
fi

# OpenBsd
if [ "$(uname)" = "OpenBSD" ]; then
echo "OpenBsd detected"
export CC=/usr/local/bin/clang
export CXX=/usr/local/bin/clang++
fi

# NetBsd
if [ "$(uname)" = "NetBSD" ]; then
echo "NetBsd detected"
export CC=/usr/pkg/bin/clang
export CXX=/usr/pkg/bin/clang++
fi

# MacOs
if [ "$(uname)" = "Darwin" ]; then
echo "MacOs detected"
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

export OPENSSL_CRYPTO_LIBRARY="/usr/local/lib/libcrypto.dylib"
export OPENSSL_SSL_LIBRARY="/usr/local/lib/libssl.dylib"
fi

cmake . -B build/