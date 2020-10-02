cmake_minimum_required(VERSION 2.8.12)
project(libcurltest)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED True)
set(C_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} parseurl.c)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})