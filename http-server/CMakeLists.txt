cmake_minimum_required(VERSION 3.10)
project(http-server VERSION 1.0)

set(C_STANDARD 11)

# group common lib file list to compile
file(GLOB_RECURSE SOURCES_COMMON LIST_DIRECTORIES true src/common/*.c)
set(SOURCES_COMMON ${SOURCES_COMMON})

file(GLOB_RECURSE SOURCES_MAIN LIST_DIRECTORIES true src/main/*.c)
set(SOURCES_MAIN ${SOURCES_MAIN})

file(GLOB_RECURSE SOURCES_TEST LIST_DIRECTORIES true src/test/*.c)
set(SOURCES_TEST ${SOURCES_TEST})

include_directories(include)

# add common folder as lib
add_subdirectory(src/common)
list(APPEND EXTRA_LIBS src/common)

add_subdirectory(src/main)
add_subdirectory(src/test)