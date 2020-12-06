#!/bin/sh

./configure.sh

#cmake -DOPENSSL_CRYPTO_LIBRARY="/usr/local/lib/libcrypto.dylib" -DOPENSSL_SSL_LIBRARY="/usr/local/lib/libssl.dylib" . -B build/
#cmake . -B build/

cmake --build build/

