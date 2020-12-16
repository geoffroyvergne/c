cmake_minimum_required(VERSION 3.7)

set(C_STANDARD 11)

project(sdlsimple)

find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIRS})

add_executable(sdlsimple main.c)
target_link_libraries(sdlsimple ${SDL_LIBRARIES})
