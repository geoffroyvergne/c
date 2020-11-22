cmake_minimum_required(VERSION 2.8.12)
project(libcurltest)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED True)
set(C_STANDARD 11)

#include(FetchContent)

set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED) 
#add_executable (curl-demo convert.cpp)
include_directories(${CURL_INCLUDE_DIR})
#target_link_libraries(curl-demo ${CURL_LIBRARIES})

#FetchContent_MakeAvailable(curl)

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()

add_executable(${PROJECT_NAME} getinmemory.c)
#target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

# INTERFACE, OBJECT, STATIC or SHARED libraries
target_link_libraries(${PROJECT_NAME}  ${CURL_LIBRARIES})
