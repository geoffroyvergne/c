cmake_minimum_required(VERSION 3.10)
project(ssl-server VERSION 1.0)

set(C_STANDARD 11)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.c)
set(SOURCES ${SOURCES})

#mac
#ln -sn /usr/local/Cellar/openssl@1.1/1.1.1i/lib/libcrypto.1.1.dylib /usr/local/lib/libcrypto.dylib
#ln -sn /usr/local/Cellar/openssl@1.1/1.1.1i/lib/libssl.1.1.dylib /usr/local/lib/libssl.dylib

#set(OPENSSL_CRYPTO_LIBRARY /usr/local/Cellar/openssl@1.1/1.1.1i)
find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR} include)

set(BINARY ${CMAKE_PROJECT_NAME})
add_executable(${BINARY} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})
