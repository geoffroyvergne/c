cmake_minimum_required(VERSION 3.7)

set(C_STANDARD 11)

project(sdlsimple)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(sdlsimple main.c)
target_link_libraries(sdlsimple ${SDL2_LIBRARIES})
