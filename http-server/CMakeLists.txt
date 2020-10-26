cmake_minimum_required(VERSION 3.10)
project(http-server VERSION 1.0)

set(C_STANDARD 11)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.c)
set(SOURCES ${SOURCES})

include_directories(include)

set(BINARY ${CMAKE_PROJECT_NAME})
add_executable(${BINARY} ${SOURCES})
