cmake_minimum_required(VERSION 3.10)
project(cutest VERSION 1.0)

set(C_STANDARD 11)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.c)
set(SOURCES_COMMON ${SOURCES})

include_directories(include)

add_executable(cutest ${SOURCES})
