#cmake_minimum_required(VERSION 2.8.12)
project(use-after-free)

set(C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

add_compile_options(-fsanitize=address -fno-omit-frame-pointer -Wall -Wextra)

add_executable(${PROJECT_NAME} use-after-free.c)
